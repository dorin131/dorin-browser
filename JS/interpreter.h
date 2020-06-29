#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <list>

#include "value.h"
#include "./statements/object_statement.h"
#include "./statements/block_statement.h"

namespace js {

class Interpreter
{
public:
    Interpreter();

    Value run(std::shared_ptr<BlockStatement>);

    inline std::shared_ptr<ObjectStatement> get_global() { return global_scope; };
    inline std::list<std::shared_ptr<BlockStatement>> get_scope_stack() { return scope_stack; };

    std::shared_ptr<Node> find_in_scope(Identifier);
private:
    std::shared_ptr<ObjectStatement> global_scope = std::make_shared<ObjectStatement>();
    std::list<std::shared_ptr<BlockStatement>> scope_stack;

    void enter_scope(std::shared_ptr<BlockStatement>);
    void exit_scope();

    // Helpers
    bool is_top_level_block_statement(std::shared_ptr<BlockStatement>);
    bool is_return_statement(std::shared_ptr<Statement>);
};

} // namespace js

#endif // INTERPRETER_H
