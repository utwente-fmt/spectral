#include "RustWrapperGenerator.h"
#include "PallasException.h"
#include "SrcLookup.h"

#include <sstream>

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
        std::stringstream stream;
        stream << "fn " << functionName << "(";

        // Arg-list (vars passed as immutable references)
        for (auto it = srcVars.begin(), end = srcVars.end(); it != end; ++it)
        {
            if (it != srcVars.begin())
                stream << ", ";
            const auto varName = utils::getSrcVarName(**it);
            const auto varType = getSrcReprOfType((*it)->getType());
            stream << varName << ": " << "&" << varType;
        }
        stream << ") -> bool ";

        // Body
        stream << "{" << "\n";
        stream << expr << ";" << "\n";
        stream << "}" << "\n";

        return stream.str();
    }

    std::pair<size_t, size_t> RustWrapperGenerator::getOffsetToExprStart(
        const SrcWrapperFunction &wFun)
    {
        // TODO: Implement for Rust
        return std::make_pair(1, 0);
    }

}