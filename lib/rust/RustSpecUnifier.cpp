#include "RustSpecUnifier.h"
#include "PallasException.h"
#include "RustNameConstants.h"

#include <llvm/ADT/StringRef.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/IR/Constants.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>

namespace sourcespec2ir
{

    RustSpecUnifier::RustSpecUnifier(const bool printDebugInfo)
        : SpecUnifier(printDebugInfo)
    {
    }

    std::optional<SpecUnifier::SpecLibElement>
    RustSpecUnifier::isSrcSpecificationFunction(const llvm::Function &f)
    {
        // Implement: Make less bad, check scope

        auto fName = f.getName().str();
        auto nameDemangle = llvm::demangle(fName);
        // llvm::outs() << "Demangle " << fName << " --> " << nameDemangle << "\n";

        // Check if the name starts with the spec-namespace:
        auto nameCrop = llvm::StringRef(nameDemangle);
        if (!nameCrop.consume_front(RUST_SPEC_NAMESPACE + "::"))
            return std::nullopt;

        // Check prefix-matches
        for (auto key : PREFIX_MATCH_NAME_MAP.keys())
            if (llvm::StringRef(nameCrop).startswith(key))
                return std::make_optional(PREFIX_MATCH_NAME_MAP.at(key));

        return std::nullopt;
    }

    llvm::Type *RustSpecUnifier::getContentTypeOfADTTy(const llvm::Type &t)
    {
        if (auto *adtType = llvm::dyn_cast<llvm::StructType>(&t))
        {
            return adtType->getElementType(0);
        }
        throw utils::PallasException("Failed to extract the content-type of the ADT.");
    }

    bool RustSpecUnifier::isSrcSeqType(const llvm::StructType &t)
    {
        return t.getName().startswith(RUST_SPEC_SEQ_TYPE);
    }

    llvm::Type *RustSpecUnifier::getSrcLibFracType()
    {
        return llvm::StructType::getTypeByName(*irContext, RUST_SPEC_FRAC_TYPE);
    }

    llvm::CallInst *RustSpecUnifier::transformBoundVar(llvm::CallInst &oldCall)
    {
        /*
        The string-literal is passed as a fat-pointer in Rust, but the
        unified spec-function expects a plain pointer.
        We therefore drop the length-argument that is passed alongside the pointer.

        @alloc_74c9abed87c9bb6bbdb9b5f5dfc0d5b4 = private unnamed_addr constant <{ [1 x i8] }> <{ [1 x i8] c"i" }>, align 1
        %_4 = call i64 @_ZN9rust_spec3_bv17h9fb88f7135560942E(ptr align 1 @alloc_74c9abed87c9bb6bbdb9b5f5dfc0d5b4, i64 1)
        */

        auto retRepr = IRTypeRepresentation::getRetReprFromCall(oldCall);
        auto isPtrRet = retRepr->isReturnByParam();

        // Sanity-check signature
        if (!isPtrRet && (oldCall.arg_size() != 2 ||
                          !oldCall.getArgOperand(0)->getType()->isPointerTy() ||
                          !llvm::isa<llvm::ConstantInt>(oldCall.getArgOperand(1))))
        {
            throw utils::PallasException("Unexpected signature of bound variable");
        }
        if (isPtrRet && (oldCall.arg_size() != 3 ||
                         !oldCall.hasStructRetAttr() ||
                         !oldCall.getArgOperand(1)->getType()->isPointerTy() ||
                         !llvm::isa<llvm::ConstantInt>(oldCall.getArgOperand(2))))
        {
            throw utils::PallasException("Unexpected signature of bound variable");
        }

        // Build new arg-list
        llvm::SmallVector<llvm::Value *> newArgs;
        if (isPtrRet)
        {
            newArgs.push_back(oldCall.getArgOperand(0)); // sret
            newArgs.push_back(oldCall.getArgOperand(1)); // literal
        }
        else
        {
            newArgs.push_back(oldCall.getArgOperand(0)); // literal
        }

        auto newCall = llvm::CallInst::Create(
            getUSpecBoundVar(*retRepr), newArgs);
        applyAttrToReturn(*retRepr, newCall);
        return newCall;
    }

    llvm::CallInst *RustSpecUnifier::transformSeqPrepend(llvm::CallInst &oldCall)
    {
        // Needs custom unification because the arguments are in a
        // different order!
        auto numArgs = oldCall.arg_size();

        // Get content-typ from sret-arg
        auto cType = getContentTypeOfADT(oldCall, 0);
        auto seqType = getUSpecSeqType(cType);

        // Copy types and arguments of the passed element's representation.
        // RUST:    sret-ptr, self-ptr,     <<ELEM-REPR>>
        // TARGET:  sret-ptr, <<ELEM-REPR>>, self-ptr
        auto elemTRepr = IRTypeRepresentation::getArgReprFromCall(
            oldCall, 2, numArgs - 2);

        // Build arg-list (reordering)
        llvm::SmallVector<llvm::Value *> newArgs;
        // Sret-arg
        newArgs.push_back(oldCall.getArgOperand(0));
        // Elem-repr
        for (unsigned i = 2; i < numArgs; ++i)
            newArgs.push_back(oldCall.getArgOperand(i));
        // Seq-ptr
        newArgs.push_back(oldCall.getArgOperand(1));

        auto newCall = llvm::CallInst::Create(
            getUSpecSeqPrepend(cType, *elemTRepr), newArgs);

        // Add attributes to return-type
        addSret(newCall, 0, seqType);
        // Add Attributes to representation of the prepended element
        applyAttrToParamRepr(*elemTRepr, newCall, 1);
        // Add attributes for the passed-in sequence
        newCall->addParamAttr(numArgs - 1, llvm::Attribute::NoUndef);
        addByVal(newCall, numArgs - 1, seqType);

        return newCall;
    }

} // namespace sourcespec2ir