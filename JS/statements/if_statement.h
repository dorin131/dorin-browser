#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include "statement.h"

namespace js {

class IfStatement : public Statement
{
public:
    IfStatement();

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "IfStatement"; };
};

} // namespace js

#endif // IFSTATEMENT_H
