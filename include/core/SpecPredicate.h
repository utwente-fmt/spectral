#ifndef PALLAS_SPECPREDICATE_H
#define PALLAS_SPECPREDICATE_H

#include <optional>
#include <string>

#include "wrapper/SrcLocation.h"

namespace sourcespec2ir
{

    /**
     * Represents a definition of a predicate in a source file.
     * Abstract predicates do not have a body.
     */
    struct SpecPredicate
    {
        const bool isInline;
        const std::string name;
        const std::string args;
        const std::optional<std::string> body;
        // Location where the predicate-definition starts in the src-file
        const SrcRange srcLoc;
        // Location where the body-expression in the src-file starts.
        const SrcLocation exprLoc;

        /*
         * Regular predicate
         */
        SpecPredicate(bool isInline, std::string name, std::string args,
                      std::string body, const SrcRange srcLoc,
                      const SrcLocation exprLoc)
            : isInline(isInline),
              name(name),
              args(args),
              body(body),
              srcLoc(srcLoc),
              exprLoc(exprLoc)
        {
        }

        /*
         * Abstract predicate
         */
        SpecPredicate(std::string name, std::string args, 
            const SrcRange srcLoc, const SrcLocation exprLoc) 
            : isInline(false),
              name(name), 
              args(args), 
              body(std::nullopt),
              srcLoc(srcLoc), 
              exprLoc(exprLoc)
        {
        }

        bool isAbstract() const { return !body.has_value(); } 
    };
}

#endif // PALLAS_SPECPREDICATE_H