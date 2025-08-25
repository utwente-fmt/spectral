#include "RustCompilerDriver.h"
#include "RustSpecUnifier.h"
#include "RustSpecTransformer.h"
#include "RustWrapperGenerator.h"

namespace sourcespec2ir
{

    RustSpecTransformer::RustSpecTransformer(
        std::string specLibPath,
        std::string srcInPath, std::string outPath,
        const utils::OutputConfig &outputConfig,
        const std::string &workingDir, 
        bool runMem2Reg)
        : SourceSpecTransformer(
              std::make_unique<RustCompilerDriver>(specLibPath, workingDir),
              std::make_unique<RustSpecUnifier>(outputConfig.printUnificationInfo),
              srcInPath, outPath, outputConfig, workingDir, runMem2Reg)
    {
    }

    std::unique_ptr<SourceWrapperGenerator> 
    RustSpecTransformer::createWrapperGenerator(
        const llvm::SmallVector<SpecDeclaration> &specDeclarations)
    {
        return std::make_unique<RustWrapperGenerator>(specDeclarations);
    }
}