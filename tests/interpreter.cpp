#include <iostream>

#include "tests.h"
#include "../JS/tokenizer.h"
#include "../JS/parser.h"
#include "../JS/value.h"
#include "../JS/interpreter.h"

struct test {
    std::string code;
    js::Value::Type result_type;
    std::string result_value;
    test(std::string c, js::Value::Type r_t, std::string r_v)
        : code(c), result_type(r_t), result_value(r_v) {}
};

std::vector<test> tests = {
    test("1+2", js::Value::NUMBER, "3"),
    test("2*3;", js::Value::NUMBER, "6"),
    test("2+5*5;", js::Value::NUMBER, "27"),
    test("2 * (3 + 1);", js::Value::NUMBER, "8"),
    test("\"hello\" + \"world\"", js::Value::STRING, "helloworld"),
    test("\"hello\" + 100", js::Value::STRING, "hello100"),
    test("2 * 2; 3 * 3", js::Value::NUMBER, "9"),
    test("var x = 1", js::Value::UNDEFINED, ""),
    test("var x = 1; x", js::Value::NUMBER, "1"),
    test("var x = 10 * (3+3); x + 1;", js::Value::NUMBER, "61"),
    test("var x = 10 * (3+3); var y = x + 1; y-1;", js::Value::NUMBER, "60"),
    test("function() {}", js::Value::UNDEFINED, ""),
    test("function() { 1 + 2; };", js::Value::UNDEFINED, ""),
    test("function() { return 3; };", js::Value::UNDEFINED, ""),
    test("var f = function() { return 4; }; f()", js::Value::NUMBER, "4"),
    test("var f = function() { return 4 / 2; }; f() *3;", js::Value::NUMBER, "6"),
    test("var f = function() { var ff = function(){return 8;}; return ff(); }; f()", js::Value::NUMBER, "8"),
    test("var f = function(a) {};", js::Value::UNDEFINED, ""),
    test("var f = function(a) { return a; }; f(88)", js::Value::NUMBER, "88"),
    test("var f = function(a,b,c) { return a+b-c; }; var x = 2;", js::Value::UNDEFINED, ""),
    test("var f = function(a,b,c) { return a+b-c; }; var x = 2; f(x,x,3)", js::Value::NUMBER, "1"),
    test("function f() { return 3; };", js::Value::UNDEFINED, ""),
    test("function f() { return 4; }; f()", js::Value::NUMBER, "4"),
    test("function f(a,b,c) { return a+b-c; }; var x = 2; f(x,x,3)", js::Value::NUMBER, "1"),
    test("var x = 1; function f(){ var x = 2; return x; }; f();", js::Value::NUMBER, "2"),
    test("var x = 1; function f(){ var x = 2; return x; }; x;", js::Value::NUMBER, "1"),
    test("var dorin = function(x, y) { return x + y; }; var yo = function() { return 3; }; dorin(10, yo());", js::Value::NUMBER, "13"),
    test("{}", js::Value::OBJECT, "{}"),
    test("var o = {}", js::Value::UNDEFINED, ""),
    test("var o = {}; o;", js::Value::OBJECT, "{}"),
    test("var o = {a:1}; o;", js::Value::OBJECT, "{}"),
    test("var o = {a:1,b:2}; o;", js::Value::OBJECT, "{}"),
    test("var o = {a:1,b:2}; o.a;", js::Value::NUMBER, "1"),
    test("var o = {a:1,b:2}; o.a + o.b;", js::Value::NUMBER, "3"),
    test("var o = {a:{b:2}}; o.a.b;", js::Value::NUMBER, "2"),
    test("var o = {a:{b:{c:777}}}; o.a.b.c;", js::Value::NUMBER, "777"),
    test("var x = 4;var o = {a:{b:{c:2+5*5,d:x}}}; o.a.b.c + o.a.b.d;", js::Value::NUMBER, "31"),
};

void interpreter_tests()
{
    for (test test : tests) {
        js::Tokenizer t = js::Tokenizer(test.code);
        auto p = js::Parser(t);
        std::shared_ptr<js::Program> program;
        try {
            program = p.parse_program();
        } catch (js::SyntaxError e) {
            std::cerr << "Parsing error: " + e.message << std::endl;
            throw test_error{};
        }

        // program->dump(0);

        js::Interpreter interpreter;
        auto result = interpreter.run(program);

        ASSERT(test.code, result.get_type() == test.result_type);
        ASSERT(test.code, result.get_value() == test.result_value);

        std::cout << "PASSED: " << test.code << std::endl;
    }
}
