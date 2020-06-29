#include <iostream>
#include "interpreter.h"
#include "tokenizer.h"
#include "parser.h"

int main()
{
    std::string cmd;

    for(;;) {
        std::cout << "> ";
        std::getline(std::cin, cmd);

        js::Tokenizer t = js::Tokenizer(cmd);
        auto p = js::Parser(t);
        std::shared_ptr<js::Program> program;
        try {
            program = p.parse_program();
        } catch (js::SyntaxError e) {
            std::cerr << "Syntax error: " + e.message << std::endl;
            continue;
        }
        js::Interpreter interpreter;
        auto result = interpreter.run(program);

        std::cout << result.get_value() << std::endl;
    }

    return 0;
}
