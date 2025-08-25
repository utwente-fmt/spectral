#ifndef PALLAS_RUSTSPECTRANSFORMER_H
#define PALLAS_RUSTSPECTRANSFORMER_H

#include "SourceSpecTransformer.h"

namespace sourcespec2ir
{

    /**
     * Specialization of the SourceSpecTransformer for Rust.
     */
    class RustSpecTransformer : public SourceSpecTransformer
    {
    public:
        RustSpecTransformer(
            std::string specLibPath,
            std::string srcInPath, std::string outPath,
            const utils::OutputConfig &outputConfig, 
            const std::string &workingDir, 
            bool runMem2Reg);
    protected:
        std::unique_ptr<SourceWrapperGenerator> createWrapperGenerator(
            const llvm::SmallVector<SpecDeclaration> &specDeclarations
        ) override;
    };

}

#endif // PALLAS_RUSTSPECTRANSFORMER_H