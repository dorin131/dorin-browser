#ifndef BLOCKSTATEMENT_H
#define BLOCKSTATEMENT_H

#include <list>
#include <vector>
#include <memory>

#include "statement.h"
#include "object_statement.h"

namespace js {

class BlockStatement : public Statement, public std::enable_shared_from_this<BlockStatement>
{
public:
    BlockStatement();

    /**
     * @brief Add a SourceElement
     */
    void append(std::shared_ptr<Statement>);
    inline std::vector<std::shared_ptr<Statement>> get_elements() { return source_elements; };
    inline std::shared_ptr<Node> get_from_local_scope(Identifier i) { return local_scope.get(i); };
    inline bool is_in_local_scope(Identifier i) { return local_scope.has(i); };
    inline void set_to_local_scope(Identifier i, std::shared_ptr<Node> n) { return local_scope.set(i, n); };

    void associate_arguments(Interpreter&, std::vector<std::shared_ptr<Node>>);
    void add_parameters(std::list<Identifier>);

    inline std::shared_ptr<Node> get_parent() { return parent; };
    inline void set_parent(std::shared_ptr<Node> p) { parent = p; };

    // Overrides
    Value execute(Interpreter&) override;
    void dump(int indent) override;
    inline std::string get_type() override { return "BlockStatement"; };
private:
    /**
     * @brief A list of Statements
     */
    std::vector<std::shared_ptr<Statement>> source_elements;
    ObjectStatement local_scope;
    std::list<Identifier> parameters;

    // Parent is needed in interpreter to check whether it's a function or contitional block
    std::shared_ptr<Node> parent;
};

} // namespace js

#endif // BLOCKSTATEMENT_H
