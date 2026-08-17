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

}

#endif // PALLAS_RUSTNAMECONSTANTS_H