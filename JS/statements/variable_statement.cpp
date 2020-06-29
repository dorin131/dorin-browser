#include "variable_statement.h"
#include "../interpreter.h"

namespace js {

VariableStatement::VariableStatement(Identifier ident, std::shared_ptr<Node> expr)
    : identifier(ident), expression(expr)
{

}

void VariableStatement::dump(int indent)
{
    print_indent(indent);
    std::cout << "VariableStatement" << std::endl;
    identifier.dump(indent + 1);
    expression->dump(indent + 1);
}

Value VariableStatement::execute(Interpreter& i)
{
    i.get_scope_stack().front()->get_local_scope()->set(identifier, expression);
    return Value(Value::UNDEFINED, "");
};

} // namespace js
