#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H

#include <memory>

#include "statement.h"

namespace js {

class ReturnStatement : public Statement
{
public:
    ReturnStatement(std::shared_ptr<Node> expression);

    inline std::shared_ptr<Node> get_expression() { return expression; };
    inline void set_expression(std::shared_ptr<Node> n) { expression = n; };

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "ReturnStatement"; };
private:
    std::shared_ptr<Node> expression;
};

} // namespace js

#endif // RETURNSTATEMENT_H
