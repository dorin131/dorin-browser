#include "object_statement.h"

namespace js {

ObjectStatement::ObjectStatement()
{

}

std::shared_ptr<Node> ObjectStatement::get(Identifier i)
{
    auto search = object_map.find(i);

    if (search != object_map.end()) {
        return search->second;
    }
    return std::make_shared<Literal>(Token(Token::UNDEFINED, ""));
};

bool ObjectStatement::has(Identifier i)
{
    auto search = object_map.find(i);
    return search != object_map.end();
}

void ObjectStatement::set(Identifier ident, std::shared_ptr<Node> expr)
{
    if (has(ident)) {
        object_map.at(ident) = expr;
    } else {
        object_map.insert(std::make_pair(ident, expr));
    }
};

Value ObjectStatement::execute(Interpreter &)
{
    return Value(Value::OBJECT, "{}");
}

void ObjectStatement::dump(int indent)
{
    print_indent(indent);
    std::cout << "ObjectStatement" << std::endl;
    // print object_map
}

} // namespace js
