#ifndef PALLAS_RUSTWRAPPERGENERATOR_H
#define PALLAS_RUSTWRAPPERGENERATOR_H

#include "SourceWrapperGenerator.h"

namespace sourcespec2ir
{

    class RustWrapperGenerator : public SourceWrapperGenerator
    {
    public:
        RustWrapperGenerator(
            const std::string srcInFile,
            const llvm::ArrayRef<SpecDeclaration> specDeclarations,
            const llvm::ArrayRef<sourcespec2ir::WrapperLocMarker> wrapperMarkers,
            std::unique_ptr<SourceSyntaxResolver> syntaxResolver);

        std::string getWrapperFunctionString(
            const WrapperSignature &sig,
            const std::string &expr,
            const std::string &functionName) override;

        std::string getPredicateDefString(const std::string &name,
                                          const std::string &args,
                                          const std::string &body) override;

        std::pair<size_t, size_t> getOffsetToExprStart(
            const SrcWrapperFunction &wFun) override;

        std::pair<size_t, size_t> getOffsetToExprStart(
            const SpecPredicate &pDef) override;

        std::string getNameForWrapperFunction() override;

    protected:
        // Overwritten methods to customize the default-WrapperGenerator

        void modifySrcWithWrappers(std::list<SrcLine> &srcLines) override;

        /*
        We override the default-framework for constructing the src-level types 
        Because the Dbg-info of Rust already contains therepresentation as a 
        string and because e.g. Rust's references do not map directly to the 
        use DW_Tags.
        */
        SrcTypeRepresentation getSrcReprOfType(const llvm::DIType *type) override;

        std::string buildArgStr(const SrcTypeRepresentation &type,
                                const std::string &name) override;

    private:
        int wrapperCnt = 0;
    };

}

#endif // PALLAS_RUSTWRAPPERGENERATOR_H