#include "RustCompilerDriver.h"
#include "RustSpecUnifier.h"
#include "RustSpecTransformer.h"
#include "RustSyntaxResolver.h"
#include "RustWrapperGenerator.h"

namespace sourcespec2ir
{

    RustSpecTransformer::RustSpecTransformer(
        std::string specLibPath,
        std::string srcInPath, std::string outPath,
        llvm::SmallVector<std::string> extContractPaths,
        const utils::OutputConfig &outputConfig,
        const std::string &workingDir,
        bool runMem2Reg)
        : SourceSpecTransformer(
              std::make_unique<RustCompilerDriver>(specLibPath, workingDir),
              std::make_unique<RustSpecUnifier>(outputConfig.printUnificationInfo),
              srcInPath, outPath, extContractPaths, outputConfig, workingDir, runMem2Reg)
    {
    }

    std::unique_ptr<SourceWrapperGenerator>
    RustSpecTransformer::createWrapperGenerator(
        const llvm::SmallVector<SpecDeclaration> &specDeclarations,
        const llvm::ArrayRef<sourcespec2ir::WrapperLocMarker> wrapperMarkers)
    {
        return std::make_unique<RustWrapperGenerator>(
            getSrcInPath(), specDeclarations, wrapperMarkers, 
            createSyntaxResolver());
    }

    std::unique_ptr<SourceSyntaxResolver>
    RustSpecTransformer::createSyntaxResolver()
    {
        return std::make_unique<RustSyntaxResolver>();
    }
}