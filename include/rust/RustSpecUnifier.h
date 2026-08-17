#ifndef PALLAS_RUSTSPECUNIFIER_H
#define PALLAS_RUSTSPECUNIFIER_H

#include "SpecUnifier.h"
#include "RustNameConstants.h"

#include <llvm/ADT/StringMap.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>

namespace sourcespec2ir
{

    /**
     * Specialization of the SpecUnifier for Rust.
     */
    class RustSpecUnifier : public SpecUnifier
    {
    public:
        const llvm::StringMap<SpecLibElement> PREFIX_MATCH_NAME_MAP = {
            {RUST_SPEC_RESULT, Result},
            {RUST_SPEC_IMPLY, Imply},
            {RUST_SPEC_SCAND, ScAnd},
            {RUST_SPEC_SCOR, ScOr},
            {RUST_SPEC_SEP, SepConj},
            {RUST_SPEC_EXISTS, Exists},
            {RUST_SPEC_FORALL, Forall},
            {RUST_SPEC_FORALLS, ForallSep}
            //{"_old<", Old},
            //{"_bv<", BoundVar},
            //{"_seqNew<", SeqNew},
            //{"_seqSize<", SeqSize},
            //{"_seqGet<", SeqGet},
            //{"_seqPrepend<", SeqPrepend},
            //{"_seqEquals<", SeqEquals},
            //{"_Perm<", Perm},
            //{"_ptrBlockLength<", PtrBlockLength},
            //{"_ptrBlockOffset<", PtrBlockOffset},
            //{"_ptrLength<", PtrLength}
        };

        RustSpecUnifier(const bool printDebugInfo);

    protected:
        std::optional<SpecLibElement> isSrcSpecificationFunction(
            const llvm::Function &f) override;

        bool isSrcSeqType(const llvm::StructType &t) override;

        llvm::Type *getContentTypeOfADTTy(const llvm::Type &t) override;

        llvm::Type *getSrcLibFracType() override;
    };

}

#endif // PALLAS_RUSTSPECUNIFIER_H