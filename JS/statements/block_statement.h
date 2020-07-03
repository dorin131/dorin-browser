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
    inline std::list<std::shared_ptr<Statement>> get_elements() { return source_elements; };
    inline std::shared_ptr<ObjectStatement> get_local_scope() { return local_scope; };

    void associate_arguments(std::vector<std::shared_ptr<Node>>);
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
    std::list<std::shared_ptr<Statement>> source_elements;
    std::shared_ptr<ObjectStatement> local_scope = std::make_shared<ObjectStatement>();
    std::list<Identifier> parameters;

    // Parent is needed in interpreter to check whether it's a function or contitional block
    std::shared_ptr<Node> parent;
};

} // namespace js

#endif // BLOCKSTATEMENT_H
