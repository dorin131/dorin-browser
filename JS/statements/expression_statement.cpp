#include "expression_statement.h"

namespace js {

ExpressionStatement::ExpressionStatement(std::shared_ptr<Node> exp): expression(exp)
{

}

void ExpressionStatement::dump(int indent)
{
    print_indent(indent);
    std::cout << "ExpressionStatement\n";
    expression->dump(indent + 1);
};

Value ExpressionStatement::execute(Interpreter& i)
{
    return get_expression()->execute(i);
};

} // namespace js
