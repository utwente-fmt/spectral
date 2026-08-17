#include "RustSpecUnifier.h"
#include "PallasException.h"
#include "RustNameConstants.h"

#include <llvm/ADT/StringRef.h>
#include <llvm/Demangle/Demangle.h>
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
        // TODO: Implement similar to C++
        return nullptr;
    }

    bool RustSpecUnifier::isSrcSeqType(const llvm::StructType &t)
    {
        // TODO: Implement similar to C++
        return false;
    }

    llvm::Type *RustSpecUnifier::getSrcLibFracType()
    {
        // TODO: Implement similar to C++
        return nullptr;
    }

} // namespace sourcespec2ir