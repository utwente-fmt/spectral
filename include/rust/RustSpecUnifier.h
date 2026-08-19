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
            {RUST_SPEC_IMPLY, Imply},
            {RUST_SPEC_SCAND, ScAnd},
            {RUST_SPEC_SCOR, ScOr},
            {RUST_SPEC_SEP, SepConj},
            {RUST_SPEC_EXISTS, Exists},
            {RUST_SPEC_FORALL, Forall},
            {RUST_SPEC_FORALLS, ForallSep},
            {RUST_SPEC_OLD, Old},
            {RUST_SPEC_RESULT, Result}, 
            {RUST_SPEC_BV, BoundVar}, 
            {RUST_SPEC_FRAC_OF, FracOf}, 
            {RUST_SPEC_PERM, Perm}, 
            {RUST_SPEC_UNFOLDING, Unfolding},
            {RUST_SPEC_SEQ_NEW, SeqNew},
            {RUST_SPEC_SEQ_EQ, SeqEquals}, 
            {RUST_SPEC_SEQ_SIZE, SeqSize},
            {RUST_SPEC_SEQ_AT, SeqGet}, 
            {RUST_SPEC_SEQ_PREPEND, SeqPrepend},
            {RUST_SPEC_SEQ_SET, SeqSet}, 
            {RUST_SPEC_SEQ_SLICE, SeqSlice}
        };

        RustSpecUnifier(const bool printDebugInfo);

    protected:
        std::optional<SpecLibElement> isSrcSpecificationFunction(
            const llvm::Function &f) override;

        bool isSrcSeqType(const llvm::StructType &t) override;

        llvm::Type *getContentTypeOfADTTy(const llvm::Type &t) override;

        llvm::Type *getSrcLibFracType() override;

        llvm::CallInst *transformBoundVar(llvm::CallInst &oldCall) override;

        llvm::CallInst *transformSeqPrepend(llvm::CallInst &oldCall) override;
    };

}

#endif // PALLAS_RUSTSPECUNIFIER_H