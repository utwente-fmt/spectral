#ifndef PALLAS_RUSTWRAPPERGENERATOR_H
#define PALLAS_RUSTWRAPPERGENERATOR_H

#include "SourceWrapperGenerator.h"

namespace sourcespec2ir
{

    class RustWrapperGenerator : public SourceWrapperGenerator
    {
    public:
        RustWrapperGenerator(const llvm::ArrayRef<SpecDeclaration> specDeclarations);

        std::string getWrapperFunctionString(
            const llvm::ArrayRef<llvm::DILocalVariable *> &srcVars,
            const std::string &expr,
            const std::string &functionName,
            const llvm::DIType *returnType) override;

        std::pair<size_t, size_t> getOffsetToExprStart(
            const SrcWrapperFunction &wFun) override;

        std::string getNameForWrapperFunction() override;

    protected:
        // Overwritten methods to customize the default-WrapperGenerator
        // TODO: Check which of these are needed.
        /*
        std::string addConst(const std::string &baseType) override;
        std::string addPointer(const std::string &baseType) override;
        std::string addReference(const std::string &baseType) override;
        std::string addTypedef(const std::string &baseType,
                               const std::string &typedefName) override;
        std::string addNamespace(const std::string &parentNamespace,
                                 const std::string &childNamespace) override;
        */
       void modifySrcWithWrappers(std::vector<SrcLine> &srcLines) override;

    private: 
        int wrapperCnt = 0;
    };

}

#endif // PALLAS_RUSTWRAPPERGENERATOR_H