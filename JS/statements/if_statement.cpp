#include "if_statement.h"

namespace js {

IfStatement::IfStatement()
{

}

void IfStatement::dump(int indent)
{
    std::cout << indent << "IfStatement";
};

Value IfStatement::execute(Interpreter&)
{
    return Value(Value::UNDEFINED, "");
};

} // namespace js
