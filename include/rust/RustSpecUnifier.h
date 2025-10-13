#ifndef PALLAS_RUSTSPECUNIFIER_H
#define PALLAS_RUSTSPECUNIFIER_H

#include "SpecUnifier.h"

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


        const std::string RUST_SPEC_NAMESPACE = "rust_spec";
        // Map names of functions of the specification-library to the 
        // corresponding enum-representation.
        const llvm::StringMap<SpecLibElement> EXACT_MATCH_NAME_MAP = {
            //{"_imply(bool, bool)", Imply},
            //{"_and(bool, bool)", ScAnd},
            //{"_or(bool, bool)", ScOr},
            //{"_exists(bool, bool)", Exists},
            //{"_forall(bool, bool)", Forall},
            //{"_forallS(bool, bool)", ForallSep},
            //{"_fracOf(int, int)", FracOf}, 
            //{"_sep(bool, bool)", SepConj}
        };

        const llvm::StringMap<SpecLibElement> PREFIX_MATCH_NAME_MAP = {
            //{"_old<", Old},
            {"_result", Result},
            {"_imply", Imply}, // Check if this can be done with an exact match
            {"_and", ScAnd},
            {"_or", ScOr}, 
            {"_sep", SepConj},
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

        /*
        const std::string CPP_SPEC_FRAC_TYPE = "struct.pallasSpec::frac";
        const std::string CPP_SPEC_SEQ_TYPE_BASE = "struct.pallasSpec::seq";
        */

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