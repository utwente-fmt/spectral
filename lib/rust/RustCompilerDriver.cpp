#include "RustCompilerDriver.h"
#include "PallasException.h"

namespace sourcespec2ir
{

    RustCompilerDriver::RustCompilerDriver(std::string specLibPath,
                                         const std::string &workingDir)
        : SourceCompilerDriver(workingDir),
          specLibPath(specLibPath)
    {
    }

    std::unique_ptr<llvm::Module> RustCompilerDriver::compileSource(
        const std::string &srcFilePath, llvm::LLVMContext &context)
    {
        // TODO: Implement similar to C++
       return nullptr;
    }

}