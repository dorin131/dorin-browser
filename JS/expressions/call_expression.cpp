#include "call_expression.h"
#include "../interpreter.h"

namespace js {

CallExpression::CallExpression(std::shared_ptr<Node> exp, std::vector<std::shared_ptr<Node>> args)
    : expression(exp), arguments(args)
{

}

Value CallExpression::execute(Interpreter& i)
{
    std::shared_ptr<Node> callee = expression;

    if (expression->get_type() == "Identifier") {
        callee = i.find_in_scope(*std::static_pointer_cast<Identifier>(callee));
    }

    if (callee->get_type() == "FunctionDeclaration") {
        auto function = std::static_pointer_cast<FunctionDeclaration>(callee);
        function->get_body()->associate_arguments(i, arguments);
        function->get_body()->set_parent(function);
        return function->get_body()->execute(i);
    }

    return callee->execute(i);
}

void CallExpression::dump(int indent)
{
    print_indent(indent);
    std::cout << "CallExpression" << std::endl;
    expression->dump(indent + 1);
};

} // namespace js
