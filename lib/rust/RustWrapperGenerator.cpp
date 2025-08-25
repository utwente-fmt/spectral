#include "RustWrapperGenerator.h"
#include "PallasException.h"

namespace sourcespec2ir
{
    RustWrapperGenerator::RustWrapperGenerator(
        const llvm::ArrayRef<sourcespec2ir::SpecDeclaration> specDeclarations)
        : SourceWrapperGenerator(specDeclarations)
    {
    }

    std::string RustWrapperGenerator::getWrapperFunctionString(
        const llvm::ArrayRef<llvm::DILocalVariable *> &srcVars,
        const std::string &expr,
        const std::string &functionName, 
        const llvm::DIType *returnType)
    {
        // TODO: Implement soimilar to C++
        return "UNIMPLEMENTED";
    }

    std::pair<size_t, size_t> RustWrapperGenerator::getOffsetToExprStart(
        const SrcWrapperFunction &wFun)
    {
        // TODO: Implement for Rust
        return std::make_pair(0, 0);
    }

}