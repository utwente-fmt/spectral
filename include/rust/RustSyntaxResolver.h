#ifndef PALLAS_RUSTSYNTAXRESOLVER_H
#define PALLAS_RUSTSYNTAXRESOLVER_H

#include "SourceSyntaxResolver.h"

namespace sourcespec2ir
{

    /**
     * Driver class that invokes swiftc to compile specifications to LLVM-IR.
     */
    class RustSyntaxResolver : public SourceSyntaxResolver
    {
    public:
        RustSyntaxResolver();

        SrcTypeRepresentation getTypeForGhostArgDef(
            llvm::StringRef argDef) override;

        std::string getArgName(llvm::StringRef argDef) override;

        // Adds '&' in front of the types
        llvm::SmallVector<std::string> getGhostMethodArgs(
            llvm::StringRef impl) override;
    };

}

#endif // PALLAS_RUSTSYNTAXRESOLVER_H