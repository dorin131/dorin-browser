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

bool Value::is_truthy()
{
    return !is_falsy();
}

// https://developer.mozilla.org/en-US/docs/Glossary/Falsy
bool Value::is_falsy()
{
    if (get_type() == BOOLEAN) {
        if (get_value() == "false") return true;
    }
    if (get_type() == STRING) {
        if (get_value() == "") return true;
    }
    if (get_type() == NUMBER) {
        if (get_value() == "0") return true;
        if (get_value() == "NaN") return true;
    }
    if (get_type() == UNDEFINED) return true;

    return false;
}

} // namespace js
