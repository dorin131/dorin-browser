#include <iostream>
#include "../JS/test.cpp"
#include "../JS/tokenizer.h"
#include "../JS/parser.h"
#include "../JS/error.h"

int main(int, char**) {
    js::Tokenizer t = js::Tokenizer("var x = 1+2; x;");
    auto p = js::Parser(t);
    std::shared_ptr<js::Program> program;
    try {
        program = p.parse_program();
    } catch (js::SyntaxError e) {
        std::cerr << "Syntax error: " + e.message;
    }
    js::Interpreter interpreter;
    auto result = interpreter.run(program);

    std::cout << result.get_value() << std::endl;
}
