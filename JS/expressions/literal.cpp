#include "literal.h"

namespace js {

Literal::Literal(Token t)
{
    switch(t.get_type()) {
    case(Token::STRING):
        value = Value(Value::STRING, t.get_value());
        break;
    case(Token::NUMBER):
        value = Value(Value::NUMBER, t.get_value());
        break;
    case(Token::TRUE):
    case(Token::FALSE):
        value = Value(Value::BOOLEAN, t.get_value());
        break;
    default:
        value = Value();
    }
}

Literal::Literal(Value v)
    : value(v)
{

}

Value Literal::execute(Interpreter&)
{
    return value;
}

void Literal::dump(int indent)
{
    print_indent(indent);
    std::cout << "Literal\n";
    print_indent(indent + 1);
    std::cout << value.get_value() << std::endl;
}

} // namespace js
