#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "expression.h"

namespace js {

class Boolean: public Expression
{
public:
    Boolean(Token);

    // Overrides
    inline std::string get_type() override { return "Boolean"; };
    Value execute(Interpreter&) override;
    void dump(int indent) override;
private:
    Token token;
};

}

#endif