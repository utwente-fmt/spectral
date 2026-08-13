#include "RustCompilerDriver.h"
#include "PallasException.h"

#include <sstream>

#include <llvm/ADT/SmallString.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/SourceMgr.h>

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
        // Generate file for IR in work-dir
        std::string irFileName = "tmp_ir_source" +
                                 std::to_string(callCounter++) + ".ll";
        auto irOutPath = llvm::SmallString<128>(workingDir);
        llvm::sys::path::append(irOutPath, irFileName);
        auto irOutStr = irOutPath.str().str();

        // If the target-file already exists, delete it
        auto rmSucc = llvm::sys::fs::remove(irOutStr);
        if (rmSucc)
            throw utils::PallasException("Failed to remove existing ir-file.");

        // Run compiler to generate the IR
        std::stringstream call;
        // TODO: We could also call 'cargo rustc' instead?
        call << " rustc ";
        call << " --emit=llvm-ir ";
        call << " -g ";
        call << " -C opt-level=0";
        call << " --crate-type lib ";
        // Disable overflow-checks with '-C debug-assertions=false' ?!
        // Set language-edition to 2021 ?!
        // TODO: Do we want to set panic = "abort" ???
        // TODO: Check if MIR optimizations also have to be disabled
        call << " -o " << irOutStr;
        call << " -L " << specLibPath << "/ ";
        call << srcFilePath;

        auto eCode = std::system(call.str().c_str());
        if (eCode != 0)
            throw utils::PallasException(
                "An error occured while compiling the Rust-file.");

        // Parse the resulting file as an LLVM-IR module
        llvm::SMDiagnostic irSMDiag;
        auto irModule = llvm::parseIRFile(irOutStr, irSMDiag, context);

        if (!irModule)
        {
            // Reading the ir-file did not work
            throw utils::PallasException(
                "Failed to load the compiled Rust-file.");
        }

        return irModule;
    }

}