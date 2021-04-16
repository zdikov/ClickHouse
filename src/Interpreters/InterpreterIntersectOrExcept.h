#pragma once

#include <Core/QueryProcessingStage.h>
#include <Interpreters/IInterpreter.h>
#include <Interpreters/InterpreterSelectWithUnionQuery.h>

namespace DB
{

class Context;
class InterpreterSelectQuery;
class QueryPlan;

class InterpreterIntersectOrExcept : public IInterpreter
{
public:
    InterpreterIntersectOrExcept(const ASTPtr & query_ptr_, const Context & context_);

    /// Builds QueryPlan for current query.
    virtual void buildQueryPlan(QueryPlan & query_plan);

    BlockIO execute() override;

private:
    ASTPtr query_ptr;
    std::shared_ptr<Context> context;
    Block result_header;
    std::vector<std::unique_ptr<IInterpreterUnionOrSelectQuery>> nested_interpreters;
    static Block getCommonHeader(const Blocks & headers);

    std::unique_ptr<InterpreterSelectWithUnionQuery>
    buildCurrentChildInterpreter(const ASTPtr & ast_ptr_);
};

}
