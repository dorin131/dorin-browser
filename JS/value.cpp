#include "value.h"

namespace js {

Value::Value(Type type, std::string value)
    : type(type), value(value)
{

}

Value::Type Value::get_type()
{
    return type;
}

std::string Value::get_value()
{
    return value;
}

} // namespace js
