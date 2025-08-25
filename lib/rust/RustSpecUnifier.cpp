#include "RustSpecUnifier.h"
#include "PallasException.h"

namespace sourcespec2ir
{

    RustSpecUnifier::RustSpecUnifier(const bool printDebugInfo)
        : SpecUnifier(printDebugInfo)
    {
    }

    std::optional<SpecUnifier::SpecLibElement>
    RustSpecUnifier::isSrcSpecificationFunction(const llvm::Function &f)
    {
        // TODO: Implement similar to C++
        return std::nullopt;
    }

    llvm::Type *RustSpecUnifier::getContentTypeOfADTTy(const llvm::Type &t)
    {
        // TODO: Implement similar to C++
        return nullptr;
    }

    bool RustSpecUnifier::isSrcSeqType(const llvm::StructType &t)
    {
        // TODO: Implement similar to Rust
        return false;
    }

    llvm::Type *RustSpecUnifier::getSrcLibFracType()
    {
        // TODO: Implement similar to Rust
        return nullptr;
    }

} // namespace sourcespec2ir