#ifndef TOKEN_H
#define TOKEN_H

#include <map>

namespace js {

class Token
{
public:
    enum Type {
        /* Identifiers */
        IDENTIFIER,

        /* Literals */
        NUMBER,
        STRING,

        /* Keywords */
        UNDEFINED,
        FUNCTION,
        VAR,
        RETURN,
        TRUE,
        FALSE,
        IF,
        FOR,
        ELSE,

        /* Compare operators */
        EQ,
        NE,
        LT,
        GT,
        LTE,
        GTE,

        /* Assignment operators */
        ASSIGN,

        /* Binary operators */
        ADD,
        SUB,
        MUL,
        DIV,

        /* Other */
        PERIOD,
        LBRACK,
        RBRACK,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        COLON,
        SEMICOLON,
        COMMA,

        /* Unary operators */
        NOT,

        /* Not able to scan */
        ILLEGAL,

        /* End of source */
        EOS,
    };

    const static std::map<std::string, Type> keywords;

    Token(Type type, std::string value);
    Token(Type type, char value);

    inline Type get_type() { return type; };
    inline std::string get_value() const { return value; };

    bool operator==(Token lhs) const;
private:
    Type type;
    std::string value;
};

} // namespace js

#endif // TOKEN_H
