#ifndef CALLEXPRESSION_H
#define CALLEXPRESSION_H

#include "expression.h"
#include "identifier.h"
#include "../statements/function_declaration.h"

namespace js {

class CallExpression : public Expression
{
public:
    CallExpression(std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>);

    // Overrides
    inline std::string get_type() override { return "CallExpression"; };
    Value execute(Interpreter&) override;
    void dump(int indent) override;
private:
    std::shared_ptr<Node> expression;
    std::vector<std::shared_ptr<Node>> arguments;
};

} // namespace js

#endif // CALLEXPRESSION_H
