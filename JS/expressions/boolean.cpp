#include "boolean.h"

namespace js {

Boolean::Boolean(Token t): token(t)
{

}

Value Boolean::execute(Interpreter&)
{
    return Value(Value::BOOLEAN, token.get_value());
}

void Boolean::dump(int indent)
{
    print_indent(indent);
    std::cout << "Boolean" << std::endl;
    print_indent(indent + 1);
    std::cout << token.get_value() << std::endl;
};

}
