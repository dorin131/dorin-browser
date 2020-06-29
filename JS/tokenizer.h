#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <string>

#include "token.h"

namespace js {

class Tokenizer
{
public:
    Tokenizer(std::string code);
    Token next_token();

private:
    std::string code;
    int position = 0;
    int read_position = 0;
    char ch;

    void read_char();
    char peek_char();
    bool is_digit();
    bool is_single_quote();
    bool is_double_quote();
    bool is_letter();
    void skip_whitespace();
    std::string read_identifier();
    std::string read_until(char);
    std::string read_number();
    Token::Type get_identifier_type(std::string);
};

} // namespace js

#endif // TOKENIZER_H
