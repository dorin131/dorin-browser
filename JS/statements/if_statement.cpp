#include "if_statement.h"

namespace js {

IfStatement::IfStatement(std::shared_ptr<Node> cond, std::shared_ptr<Node> t)
    : condition(cond), then_block(t)
{

}

IfStatement::IfStatement(std::shared_ptr<Node> cond, std::shared_ptr<Node> t, std::shared_ptr<Node> e)
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
    std::cout << "Else" << std::endl;
    else_block->dump(indent+2);
};

Value IfStatement::execute(Interpreter& i)
{
    if (condition->execute(i).is_truthy()) {
        return then_block->execute(i);
    }
    return else_block->execute(i);
};



} // namespace js
