#ifndef VARIABLESTATEMENT_H
#define VARIABLESTATEMENT_H

#include <memory>

#include "statement.h"
#include "../expressions/expression.h"
#include "../expressions/identifier.h"

namespace js {

class VariableStatement : public Statement
{
public:
    VariableStatement(Identifier ident, std::shared_ptr<Node> expr);

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "VariableStatement"; };
private:
    Identifier identifier;
    std::shared_ptr<Node> expression;
};
} // namespace js

#endif // VARIABLESTATEMENT_H
