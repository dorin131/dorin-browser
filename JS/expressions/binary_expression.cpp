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

    if (op == "+") {
        if (l.get_type() == Value::STRING || r.get_type() == Value::STRING) {
            return string_arithmetic(l, r);
        }
        return number_arithmetic(l, r);
    } else if (op == "-" || op == "*" || op == "/") {
        return number_arithmetic(l, r);
    } else {
        return comparison(l, r);
    }
}

Value BinaryExpression::string_arithmetic(Value l, Value r)
{
    if (op != "+") {
        throw SyntaxError("Cannot use operator on strings: " + op);
    }
    return Value(Value::STRING, l.get_value() + r.get_value());
}

Value BinaryExpression::number_arithmetic(Value l, Value r)
{
    int l_int = value_to_int(l);
    int r_int = value_to_int(r);

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

Value BinaryExpression::comparison(Value l, Value r)
{
    int l_int;
    int r_int;

    if (l.get_type() == Value::STRING && r.get_type() != Value::STRING) {
        l_int = str_to_int(l.get_value());
        if (l_int == -1) return Value(Value::BOOLEAN, "false");
        r_int = value_to_int(r);
    }

    if (r.get_type() == Value::STRING && l.get_type() != Value::STRING) {
        r_int = str_to_int(r.get_value());
        if (r_int == -1) return Value(Value::BOOLEAN, "false");
        l_int = value_to_int(l);
    }

    if (l.get_type() != Value::STRING && r.get_type() != Value::STRING) {
        l_int = value_to_int(l);
        r_int = value_to_int(r);
    }

    if (l.get_type() == Value::STRING && r.get_type() == Value::STRING) {
        return string_comparison(l, r);
    }

    if (op == "==") {
        return Value(Value::BOOLEAN, bool_to_str(l_int == r_int));
    } else if (op == "!=") {
        return Value(Value::BOOLEAN, bool_to_str(l_int != r_int));
    } else if (op == ">") {
        return Value(Value::BOOLEAN, bool_to_str(l_int > r_int));
    } else if (op == "<") {
        return Value(Value::BOOLEAN, bool_to_str(l_int < r_int));
    } else if (op == ">=") {
        return Value(Value::BOOLEAN, bool_to_str(l_int >= r_int));
    } else if (op == "<=") {
        return Value(Value::BOOLEAN, bool_to_str(l_int <= r_int));
    }
    throw SyntaxError("Invalid operator: " + op);
}

Value BinaryExpression::string_comparison(Value l, Value r)
{
    if (op == "==") {
        return Value(Value::BOOLEAN, bool_to_str(l.get_value() == r.get_value()));
    } else if (op == "!=") {
        return Value(Value::BOOLEAN, bool_to_str(l.get_value() != r.get_value()));
    } else if (op == ">") {
        return Value(Value::BOOLEAN, bool_to_str(l.get_value() > r.get_value()));
    } else if (op == "<") {
        return Value(Value::BOOLEAN, bool_to_str(l.get_value() < r.get_value()));
    } else if (op == ">=") {
        return Value(Value::BOOLEAN, bool_to_str(l.get_value() >= r.get_value()));
    } else if (op == "<=") {
        return Value(Value::BOOLEAN, bool_to_str(l.get_value() <= r.get_value()));
    }
    throw SyntaxError("Invalid operator: " + op);
}

int BinaryExpression::str_to_int(std::string s)
{
    if ((s.size() == 0) || (s.find_first_not_of(" \t\n\v\f\r") == std::string::npos)) {
        return 0;
    }
    try {
        return std::stoi(s);
    } catch (...) {
        return -1; // NaN
    }
}

std::string BinaryExpression::bool_to_str(bool expr)
{
    return expr ? "true" : "false";
}

int BinaryExpression::value_to_int(Value v)
{
    std::string val = v.get_value();
    if (v.get_type() == Value::BOOLEAN) {
        return val == "true" ? 1 : 0;
    }
    try {
        return std::stoi(val);
    } catch (...) {
        throw SyntaxError("Cannot convert " + val + " to a number");
    }
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
