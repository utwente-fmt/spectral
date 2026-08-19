#include "RustSyntaxResolver.h"
#include "PallasException.h"

#include <sstream>

namespace sourcespec2ir
{

    RustSyntaxResolver::RustSyntaxResolver() {}

    SrcTypeRepresentation RustSyntaxResolver::getTypeForGhostArgDef(
        llvm::StringRef argDef)
    {
        // Find the ':' that separates the type
        auto [n, t] = argDef.trim().split(':');
        if (t.empty()) {
            std::stringstream s;
            s << "Failed to extract type from ghost argument definition: "
                   << argDef.str();
            throw utils::PallasException(s.str());
        } 

        return SrcTypeRepresentation(t.trim().str());
    }

    std::string RustSyntaxResolver::getArgName(llvm::StringRef argDef)
    {
        // Find the ':' that separates the type
        auto [n, t] = argDef.trim().split(':');
        return n.trim().str();
    }

}