#include "block_statement.h"
#include "../interpreter.h"

namespace js {

BlockStatement::BlockStatement()
{

}

void BlockStatement::append(std::shared_ptr<Statement> source_element)
{
    source_elements.push_back(source_element);
}

Value BlockStatement::execute(Interpreter& i)
{
    return i.run(shared_from_this());
};

void BlockStatement::add_parameters(std::list<Identifier> params)
{
    parameters = params;
}

void BlockStatement::associate_arguments(std::vector<std::shared_ptr<Node>> args)
{
    int i = 0;
    for(Identifier id : parameters) {
        get_local_scope()->set(id, args[i]);
        i++;
    }
}

void BlockStatement::dump(int indent)
{
    print_indent(indent);
    std::cout << "BlockStatement" << std::endl;
    if (source_elements.size() > 0) {
        for (std::shared_ptr<Statement> st : source_elements) {;
            st->dump(indent + 1);
        }
    }
};

} // namespace js
