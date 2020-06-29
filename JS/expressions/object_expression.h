#ifndef OBJECTEXPRESSION_H
#define OBJECTEXPRESSION_H

#include <list>

#include "expression.h"
#include "../interpreter.h"
#include "../statements/object_statement.h"

namespace js {

class ObjectExpression : public Expression
{
public:
    ObjectExpression(Identifier, std::list<Identifier>);

    inline Identifier get_name() { return name; };
    inline std::list<Identifier> get_path() { return path; };

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "ObjectExpression"; };
private:
    Identifier name;
    std::list<Identifier> path;
};

} // namespace js

#endif // OBJECTEXPRESSION_H
