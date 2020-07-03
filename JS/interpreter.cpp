#include "interpreter.h"

namespace js {

Interpreter::Interpreter()
{

}

Value Interpreter::run(std::shared_ptr<BlockStatement> block_statement)
{
    bool has_returned = false;
    Value last_value = Value(Value::UNDEFINED, "");

    enter_scope(block_statement);
    for (std::shared_ptr<Statement> statement : block_statement->get_elements()) {
        last_value = statement->execute(*this);

        if (is_return_statement(statement)) {
            if (!is_in_a_function()) throw;
            has_returned = true;
            break;
        }
    }

    auto top_level = is_top_level_block_statement(block_statement);
    auto in_conditional_stmt = is_in_conditional_stmt(block_statement);

    exit_scope();

    if (in_conditional_stmt) return last_value;

    if (!has_returned && !top_level) {
        return Value(Value::UNDEFINED, "");
    }

    return last_value;
}

void Interpreter::enter_scope(std::shared_ptr<BlockStatement> block_statement)
{
    scope_stack.push_front(block_statement);
}

void Interpreter::exit_scope()
{
    scope_stack.pop_front();
}

bool Interpreter::is_top_level_block_statement(std::shared_ptr<BlockStatement> block_statement)
{
    return block_statement->get_type() == "Program";
}

bool Interpreter::is_return_statement(std::shared_ptr<Statement> node)
{
    return node->get_type() == "ReturnStatement";
}

bool Interpreter::is_in_a_function()
{
    // TODO: to implement
    return true;
}

bool Interpreter::is_in_conditional_stmt(std::shared_ptr<BlockStatement> b)
{
    auto parent = b->get_parent();
    if (!parent) return false;
    return parent->get_type() == "IfStatement";
}

std::shared_ptr<Node> Interpreter::find_in_scope(Identifier ident)
{
    for(std::shared_ptr<BlockStatement> block : scope_stack) {
        if(block->get_local_scope()->has(ident)) {
            return block->get_local_scope()->get(ident);
        }
    }
    return get_global()->get(ident);
}

} //namespace js
