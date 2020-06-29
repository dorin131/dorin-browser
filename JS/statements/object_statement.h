#ifndef OBJECTLITERALEXPRESSION_H
#define OBJECTLITERALEXPRESSION_H

#include <memory>

#include "statement.h"
#include "../expressions/identifier.h"
#include "../expressions/literal.h"

namespace js {

class ObjectStatement : public Statement
{
public:
    ObjectStatement();

    std::shared_ptr<Node> get(Identifier);
    bool has(Identifier);
    void set(Identifier, std::shared_ptr<Node>);

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "ObjectStatement"; };
private:
    std::map<Identifier, std::shared_ptr<Node>> object_map;
    inline std::map<Identifier, std::shared_ptr<Node>> get_map() { return object_map; };
};

} // namespace js

#endif // OBJECTLITERALEXPRESSION_H
