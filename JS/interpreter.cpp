#include "interpreter.h"

namespace js {

Interpreter::Interpreter()
{

}

Value Interpreter::run(std::shared_ptr<BlockStatement> block_statement)
{
    bool has_returned = false;
    Value last_value = Value();

    enter_scope(block_statement);

    /**
     * Loop over all statements of the current block statement
     **/
    auto statements = block_statement->get_elements();
    auto size = statements.size();
    for (size_t it = 0; it < size; it++) {
        last_value = statements[it]->execute(*this);

        /**
         * Get the correct branch (block statement) and insert its statements
         * in the current block statement at the current index
         **/
        if (statements[it]->get_type() == "IfStatement") {
            auto branch = std::static_pointer_cast<IfStatement>(statements[it])->get_branch(*this);
            if (branch) {
                auto branch_statements = branch->get_elements();
                statements.insert(statements.begin() + int(it) + 1, branch_statements.begin(), branch_statements.end());
                size += branch_statements.size();
            }
        }

        if (is_return_statement(statements[it])) {
            if (!in_function_count) throw SyntaxError("Illegal return statement");
            has_returned = true;
            break;
        }
    }

    auto top_level = is_top_level_block_statement(block_statement);

    exit_scope();

    if (!has_returned && !top_level) {
        return Value();
    }

    return last_value;
}

void Interpreter::enter_scope(std::shared_ptr<BlockStatement> block_statement)
{
    scope_stack.push_front(block_statement);
    if (is_in_a_function()) in_function_count++;
}

void Interpreter::exit_scope()
{
    if (is_in_a_function()) in_function_count--;
    scope_stack.pop_front();
}

bool Interpreter::is_in_a_function()
{
    auto parent = scope_stack.front()->get_parent();
    return parent && parent->get_type() == "FunctionDeclaration";
}

bool Interpreter::is_top_level_block_statement(std::shared_ptr<BlockStatement> block_statement)
{
    return block_statement->get_type() == "Program";
}

bool Interpreter::is_return_statement(std::shared_ptr<Statement> node)
{
    return node->get_type() == "ReturnStatement";
}

std::shared_ptr<Node> Interpreter::find_in_scope(Identifier ident)
{
    for(std::shared_ptr<BlockStatement> block : scope_stack) {
        if(block->is_in_local_scope(ident)) {
            return block->get_from_local_scope(ident);
        }
    }
    return get_global()->get(ident);
}

} //namespace js
