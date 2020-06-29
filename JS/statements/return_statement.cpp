#include "return_statement.h"

namespace js {

ReturnStatement::ReturnStatement(std::shared_ptr<Node> exp)
    : expression(exp)
{

}

void ReturnStatement::dump(int indent)
{
    print_indent(indent);
    std::cout << "ReturnStatement" << std::endl;
    expression->dump(indent + 1);
};

Value ReturnStatement::execute(Interpreter& i)
{
    return expression->execute(i);
};

} // namespace js
