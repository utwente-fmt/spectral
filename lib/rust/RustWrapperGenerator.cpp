#include "RustWrapperGenerator.h"

#include "PallasException.h"
#include "RustNameConstants.h"
#include "SrcLookup.h"
#include "FileUtils.h"

#include <sstream>

namespace sourcespec2ir
{
    RustWrapperGenerator::RustWrapperGenerator(
        const std::string srcInFile,
        const llvm::ArrayRef<SpecDeclaration> specDeclarations,
        const llvm::ArrayRef<sourcespec2ir::WrapperLocMarker> wrapperMarkers,
        std::unique_ptr<SourceSyntaxResolver> syntaxResolver)
        : SourceWrapperGenerator(
              srcInFile, specDeclarations, wrapperMarkers,
              std::move(syntaxResolver))
    {
    }

    std::string RustWrapperGenerator::getWrapperFunctionString(
        const WrapperSignature &sig,
        const std::string &expr,
        const std::string &functionName)
    {
        auto rType = sig.returnTy.has_value()
                         ? sig.returnTy.value().prefix.str().str()
                         : "bool";

        std::stringstream stream;

        // Build wrapper itself:
        // Force codegen of wrapper even though it is not called
        stream << "#[no_mangle]\n"
               << "#[allow(unused_variables)]\n"
               << "#[allow(unused_imports)]\n"
               << "fn " << functionName << "(";

        // Arg-list (vars passed as immutable references)
        bool first = true;
        for (auto &arg : sig.args)
        {
            // Skip 'self'-arg as it gets added implicitly
            if (arg.ends_with(" self"))
                continue;
            if (!first)
                stream << ", ";
            stream << arg;
            first = false;
        }

        stream << ") -> " << rType << " {\n"
               << "use rust_spec::*;\n"
               << expr << "\n"
               << "}" << "\n";

        return stream.str();
    }

    std::pair<size_t, size_t> RustWrapperGenerator::getOffsetToExprStart(
        const SrcWrapperFunction &wFun)
    {
        return std::make_pair(2, 0);
    }

    std::string RustWrapperGenerator::getPredicateDefString(
        const std::string &name, const std::string &args,
        const std::string &body)
    {
        std::stringstream stream;

        stream << "#[no_mangle]\n"
               << "#[allow(unused_variables)]\n"
               << "#[allow(unused_imports)]\n"
               << "fn " << name << "(";

        llvm::SmallVector<llvm::StringRef> argVec;
        llvm::StringRef(args).split(argVec, ',');
        bool first = true;
        for (auto arg : argVec)
        {
            auto [name, type] = arg.split(':');
            if (!first)
                stream << ", ";
            stream << name.str() << ": &" << type.str();
            first = false;
        }

        stream << ") -> bool {\n"
               << "use rust_spec::*;\n"
               << body << "\n"
               << "}\n";

        return stream.str();
    }

    std::pair<size_t, size_t> RustWrapperGenerator::getOffsetToExprStart(
        const SpecPredicate &pDef)
    {
        return std::make_pair(2, 0);
    }

    std::string RustWrapperGenerator::getNameForWrapperFunction()
    {
        return RUST_WRAPPER_PREFIX + std::to_string(wrapperCnt++);
    }

    std::string RustWrapperGenerator::buildArgStr(
        const SrcTypeRepresentation &type, const std::string &name)
    {
        if (!type.suffix.empty())
            throw utils::PallasException(
                "Unexpected suffix in type representation");
        return name + ": &" + type.prefix.str().str();
    }

    void RustWrapperGenerator::modifySrcWithWrappers(std::list<SrcLine> &srcLines)
    {
        // Add content of the declaration-block to the file.
        for (auto &decl : specDeclarations)
        {
            auto declStr = decl.content + ";";
            auto insertPos = findInsertPos(
                decl.srcLoc.getStartLine(), srcLines);
            insertLines(srcLines, declStr, insertPos);
        }
    }

    void RustWrapperGenerator::addPointer(
        SrcTypeRepresentation &baseType, const llvm::DIDerivedType &type)
    {
        if (type.getName().starts_with("&mut")) {
            // Prepend '&mut '
            llvm::StringRef r = "&mut ";
            baseType.prefix.insert(baseType.prefix.begin(), r.begin(), r.end());
        } else if (type.getName().starts_with("&")) {
            // Prepend '& '
            llvm::StringRef r = "& ";
            baseType.prefix.insert(baseType.prefix.begin(), r.begin(), r.end());
        } else {
            throw utils::PallasException(
                "Encountered an unsupported DW_TAG_pointer_type.");
        }
    }

    std::string RustWrapperGenerator::addNamespace(
        const std::string &parentNamespace, const std::string &childNamespace)
    {
        // In some cases, the name of the current file is added to the namespace
        // This case needs to be skipped. 
        auto filename = utils::filenameWithoutExtension(srcInFile);
        if (parentNamespace.empty() && childNamespace == filename) {
            return "";
        }

        return parentNamespace + childNamespace + "::";
    }

}