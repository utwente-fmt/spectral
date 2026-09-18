#ifndef PALLAS_RUSTNAMECONSTANTS_H
#define PALLAS_RUSTNAMECONSTANTS_H

#include <string>

namespace sourcespec2ir
{
    /**
     * Various constants that are used by the Rust frontend
     */

    // Prefix of generated wrapper-functions
    const std::string RUST_WRAPPER_PREFIX = "pallas_spec_";

    const std::string RUST_SPEC_NAMESPACE = "rust_spec";

    const std::string RUST_SPEC_IMPLY = "_imply";
    const std::string RUST_SPEC_SCAND = "_and";
    const std::string RUST_SPEC_SCOR = "_or";
    const std::string RUST_SPEC_SEP = "_sep";
    const std::string RUST_SPEC_RESULT = "_result";
    const std::string RUST_SPEC_EXISTS = "_exists";
    const std::string RUST_SPEC_FORALL = "_forall";
    const std::string RUST_SPEC_FORALLS = "_forallS";
    const std::string RUST_SPEC_OLD = "_old";
    const std::string RUST_SPEC_BV = "_bv";
    const std::string RUST_SPEC_FRAC_OF = "Frac::of";
    const std::string RUST_SPEC_PERM = "_Perm";
    const std::string RUST_SPEC_UNFOLDING = "_unfolding";
    const std::string RUST_SPEC_SEQ_NEW = "_Seq$LT$T$GT$::new";
    const std::string RUST_SPEC_SEQ_EQ = "_Seq$LT$T$GT$::eq";
    const std::string RUST_SPEC_SEQ_SIZE = "_Seq$LT$T$GT$::size";
    const std::string RUST_SPEC_SEQ_AT = "_Seq$LT$T$GT$::at";
    const std::string RUST_SPEC_SEQ_PREPEND = "_Seq$LT$T$GT$::prepend"; 
    const std::string RUST_SPEC_SEQ_SET = "_Seq$LT$T$GT$::set"; 
    const std::string RUST_SPEC_SEQ_SLICE = "_Seq$LT$T$GT$::slice";
    const std::string RUST_SPEC_PTR_BLOCK_LENGTH = "_ptr_block_length";
    const std::string RUST_SPEC_PTR_BLOCK_OFFSET = "_ptr_block_offset";
    const std::string RUST_SPEC_PTR_LENGTH = "_ptr_length";

    const std::string RUST_SPEC_FRAC_TYPE = "rust_spec::Frac";
    const std::string RUST_SPEC_SEQ_TYPE = "rust_spec::_Seq<";
}

#endif // PALLAS_RUSTNAMECONSTANTS_H