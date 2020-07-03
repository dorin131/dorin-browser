#include "eval.h"

namespace js {

Eval::Eval()
{

}

Value Eval::run(std::string code)
{
    js::Tokenizer t = js::Tokenizer(code);
    js::Parser parser = js::Parser(t);
    std::shared_ptr<js::Program> program;
    js::Interpreter interpreter;
    Value result;
    try {
        program = parser.parse_program();
        if (debug) program->dump(0);
        result = interpreter.run(program);
    } catch (js::SyntaxError e) {
        std::cerr << "SyntaxError: " + e.message << std::endl;
        return Value(Value::ERROR, "SyntaxError: " + e.message);
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return Value(Value::ERROR, "Unknown error");
    }
    
    return result;
}

void Eval::enable_debug()
{
    debug = true;
}

}