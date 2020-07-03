#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include "statement.h"

namespace js {

class IfStatement : public Statement
{
public:
    IfStatement(std::shared_ptr<Node>, std::shared_ptr<Node>);
    IfStatement(std::shared_ptr<Node>, std::shared_ptr<Node>, std::shared_ptr<Node>);

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "IfStatement"; };
private:
    std::shared_ptr<Node> condition;
    std::shared_ptr<Node> then_block;
    std::shared_ptr<Node> else_block;
};

} // namespace js

#endif // IFSTATEMENT_H
