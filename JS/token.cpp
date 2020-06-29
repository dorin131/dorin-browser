#include "token.h"

namespace js {

Token::Token(Type type, std::string value)
{
    this->type = type;
    this->value = value;
}

Token::Token(Type type, char value)
{
    this->type = type;
    this->value = value;
}

bool Token::operator==(Token t) const
{
    return t.type == this->type && t.value == this->value;
}

const std::map<std::string, Token::Type> Token::keywords = {
    {"function", Token::FUNCTION},
    {"var", Token::VAR},
    {"return", Token::RETURN},
    {"true", Token::TRUE},
    {"false", Token::FALSE},
    {"if", Token::IF},
    {"else", Token::ELSE}
};

} // namespace js
