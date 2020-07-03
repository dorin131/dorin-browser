#ifndef VALUE_H
#define VALUE_H

#include "token.h"

namespace js {

class Value
{
public:
    enum Type {
        ERROR,
        UNDEFINED,
        NUMBER,
        STRING,
        OBJECT,
        BOOLEAN,
        FUNCTION
    };
    Value(Type, std::string);
    Type get_type();
    std::string get_value();
    bool is_truthy();
    bool is_falsy();
private:
    Type type;
    std::string value;
};

} // namespace js

#endif // VALUE_H
