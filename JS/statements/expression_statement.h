#ifndef EXPRESSIONSTATEMENT_H
#define EXPRESSIONSTATEMENT_H

#include <memory>

#include "statement.h"
#include "../expressions/expression.h"

namespace js {

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(std::shared_ptr<Node>);

    inline std::shared_ptr<Node> get_expression() { return expression; };

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "ExpressionStatement"; };
private:
    std::shared_ptr<Node> expression;
};

} //namespace js

#endif // EXPRESSIONSTATEMENT_H
