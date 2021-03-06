#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include <iostream>
#include <memory>

#include "../error.h"
#include "expression.h"

namespace js {

class BinaryExpression : public Expression
{
public:
    BinaryExpression(std::string op, std::shared_ptr<Node> left, std::shared_ptr<Node> right);

    inline std::shared_ptr<Node> get_left() { return left; };
    inline std::shared_ptr<Node> get_right() { return right; };
    inline std::string get_op() { return op; };

    // Overrides
    inline std::string get_type() override { return "BinaryExpression"; };
    Value execute(Interpreter&) override;
    void dump(int indent) override;
private:
    std::string op;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Value string_arithmetic(Value, Value);
    Value number_arithmetic(Value, Value);
    Value comparison(Value, Value);
    Value string_comparison(Value, Value);
    std::string bool_to_str(bool);
    int value_to_int(Value);
    int str_to_int(std::string);
};

} // namespace js

#endif // BINARYEXPRESSION_H
