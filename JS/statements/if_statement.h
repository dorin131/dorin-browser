#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include "statement.h"
#include "block_statement.h"

namespace js {

class IfStatement : public Statement, public std::enable_shared_from_this<IfStatement>
{
public:
    IfStatement(std::shared_ptr<Node>, std::shared_ptr<BlockStatement>);
    IfStatement(std::shared_ptr<Node>, std::shared_ptr<BlockStatement>, std::shared_ptr<BlockStatement>);

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "IfStatement"; };
private:
    std::shared_ptr<Node> condition;
    std::shared_ptr<BlockStatement> then_block;
    std::shared_ptr<BlockStatement> else_block;
};

} // namespace js

#endif // IFSTATEMENT_H
