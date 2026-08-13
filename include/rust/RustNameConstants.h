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

    // TODO: Move the names of the spec-lib here!
}

#endif // PALLAS_RUSTNAMECONSTANTS_H