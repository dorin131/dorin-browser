#include "binary_expression.h"

namespace js {

BinaryExpression::BinaryExpression(std::string op, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : op(op), left(left), right(right)
{

}

Value BinaryExpression::execute(Interpreter& i)
{
    Value l = left->execute(i);
    Value r = right->execute(i);

    if (l.get_type() == Value::STRING || r.get_type() == Value::STRING) {
        return string_arithmetic(l, r);
    }
    return number_arithmetic(l, r);
}

Value BinaryExpression::string_arithmetic(Value l, Value r) const
{
    if (op != "+") {
        throw SyntaxError("Cannot use operator on strings: " + op);
    }
    return Value(Value::STRING, l.get_value() + r.get_value());
}

Value BinaryExpression::number_arithmetic(Value l, Value r) const
{
    int l_int = std::stoi(l.get_value());
    int r_int = std::stoi(r.get_value());

    if (op == "+") {
        return Value(Value::NUMBER, std::to_string(l_int + r_int));
    } else if (op == "-") {
        return Value(Value::NUMBER, std::to_string(l_int - r_int));
    } else if (op == "*") {
        return Value(Value::NUMBER, std::to_string(l_int * r_int));
    } else if (op == "/") {
        return Value(Value::NUMBER, std::to_string(l_int / r_int));
    }
    throw SyntaxError("Invalid operator: " + op);
}

void BinaryExpression::dump(int indent)
{
    print_indent(indent);
    std::cout << "BinaryExpression" << std::endl;
    print_indent(indent + 1);
    std::cout << op << std::endl;
    left->dump(indent + 1);
    right->dump(indent + 1);
};

} // namespace js
