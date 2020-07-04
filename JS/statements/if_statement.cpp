#include "if_statement.h"

namespace js {

IfStatement::IfStatement(std::shared_ptr<Node> cond, std::shared_ptr<BlockStatement> t)
    : condition(cond), then_block(t)
{

}

IfStatement::IfStatement(std::shared_ptr<Node> cond, std::shared_ptr<BlockStatement> t, std::shared_ptr<BlockStatement> e)
    : condition(cond), then_block(t), else_block(e)
{

}

void IfStatement::dump(int indent)
{
    print_indent(indent);
    std::cout << "IfStatement" << std::endl;
    print_indent(indent+1);
    std::cout << "Condition" << std::endl;
    condition->dump(indent+2);
    print_indent(indent+1);
    std::cout << "Then" << std::endl;
    then_block->dump(indent+2);
    print_indent(indent+1);
    if (else_block) {
        std::cout << "Else" << std::endl;
        else_block->dump(indent+2);
    }
};

Value IfStatement::execute(Interpreter& i)
{
    /**
     * IfStatement should not be executed, rather you should get
     * the branch with get_branch and insert the statements into
     * the parent block statement
     **/
    return Value();
};

std::shared_ptr<BlockStatement> IfStatement::get_branch(Interpreter& i)
{
    if (condition->execute(i).is_truthy()) {
        then_block->set_parent(shared_from_this());
        return then_block;
    }
    if (else_block) {
        else_block->set_parent(shared_from_this());
        return else_block;
    }
    return nullptr;
}

} // namespace js
