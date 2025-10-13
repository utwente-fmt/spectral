#include "RustWrapperGenerator.h"

#include "PallasException.h"
#include "RustNameConstants.h"
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
        // TODO: Find another way to disable compiler from removing unsed
        //  functions. pub will not always work.
        stream << "#[allow(unused_variables)]\n";
        stream << "pub fn " << functionName << "(";

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
        stream << expr << "\n";
        stream << "}" << "\n";

        return stream.str();
    }

    std::pair<size_t, size_t> RustWrapperGenerator::getOffsetToExprStart(
        const SrcWrapperFunction &wFun)
    {
        // TODO: Implement for Rust
        return std::make_pair(2, 0);
    }

    std::string RustWrapperGenerator::getNameForWrapperFunction()
    {
        return RUST_WRAPPER_PREFIX + std::to_string(wrapperCnt++);
    }

    void RustWrapperGenerator::modifySrcWithWrappers(std::vector<SrcLine> &srcLines)
    {

        // Add content of the declaration-block to the file.
        for (auto &decl : specDeclarations)
        {
            auto declStr = decl.content + ";";
            auto insertPos = findInsertPos(decl.srcFileLine, srcLines);
            insertLines(srcLines, declStr, insertPos);
        }

        // Add include for the specification-library to the top of the
        // generated file.
        // This has to be placed under the #![no_main] macro if present
        // srcLines.insert(srcLines.begin(),
        //                SrcLine("#include \"cpp_spec_lib.h\"", 0));
        // TODO: Add a use::rust_spec to the top of the file.
    }

}