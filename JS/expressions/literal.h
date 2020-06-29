#ifndef LITERAL_H
#define LITERAL_H

#include "expression.h"
#include "../token.h"

namespace js {

class Literal : public Expression
{
public:
    Literal(Token);

    inline Token get_token() { return token; };

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "Literal"; };
private:
    Token token;
};

} // namespace js

#endif // LITERAL_H
