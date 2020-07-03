#ifndef INTERPRETER_TEST_H
#define INTERPRETER_TEST_H

#include <iostream>

#include "tests.h"
#include "../JS/tokenizer.h"
#include "../JS/parser.h"
#include "../JS/value.h"
#include "../JS/interpreter.h"

namespace tests {

struct test {
    std::string code;
    js::Value::Type result_type;
    std::string result_value;
    test(std::string c, js::Value::Type r_t, std::string r_v)
        : code(c), result_type(r_t), result_value(r_v) {}
};

std::vector<test> all_tests = {
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
    test("var f = function(a) { 1; };", js::Value::UNDEFINED, ""),
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
    test("true", js::Value::BOOLEAN, "true"),
    test("false", js::Value::BOOLEAN, "false"),
    test("var b = true; b;", js::Value::BOOLEAN, "true"),
    test("1 + true", js::Value::NUMBER, "2"),
    test("true + true", js::Value::NUMBER, "2"),
    test("true + \"hello\"", js::Value::STRING, "truehello"),
    test("1 == 1", js::Value::BOOLEAN, "true"),
    test("1 != 1", js::Value::BOOLEAN, "false"),
    test("1 == 2", js::Value::BOOLEAN, "false"),
    test("1 == \"1\"", js::Value::BOOLEAN, "true"),
    test("true == false", js::Value::BOOLEAN, "false"),
    test("true == true", js::Value::BOOLEAN, "true"),
    test("\"hello\" == \"world\"", js::Value::BOOLEAN, "false"),
    test("\"hello\" == \"hello\"", js::Value::BOOLEAN, "true"),
    test("\"hello\" == 1", js::Value::BOOLEAN, "false"),
    test("\"hello\" == true", js::Value::BOOLEAN, "false"),
    test("\"hello\" == false", js::Value::BOOLEAN, "false"),
    test("\"\" == false", js::Value::BOOLEAN, "true"),
    test("\" \" == false", js::Value::BOOLEAN, "true"),
    test("\"hello\" > \"world\"", js::Value::BOOLEAN, "false"),
    test("\"hello\" < \"world\"", js::Value::BOOLEAN, "true"),
    test("\"hello\" != \"world\"", js::Value::BOOLEAN, "true"),
    test("\"hello\" >= \"world\"", js::Value::BOOLEAN, "false"),
    test("\"hello\" <= \"world\"", js::Value::BOOLEAN, "true"),
    test("1 < 2", js::Value::BOOLEAN, "true"),
    test("1 > 2", js::Value::BOOLEAN, "false"),
    test("1 <= 2", js::Value::BOOLEAN, "true"),
    test("1 >= 2", js::Value::BOOLEAN, "false"),
    test("if (true) { 1; } else { 2; };", js::Value::NUMBER, "1"),
    test("if (false) { 1; } else { 2; };", js::Value::NUMBER, "2"),
    test("if (5==5) { 1; } else { 2; };", js::Value::NUMBER, "1"),
    test("if (5==10) { 1; } else { 2; };", js::Value::NUMBER, "2"),
    test("if (\"hello\") { 1; } else { 2; };", js::Value::NUMBER, "1"),
    test("if (\"\") { 1; } else { 2; };", js::Value::NUMBER, "2"),
};

void interpreter_tests()
{
    for (test test : all_tests) {
        js::Tokenizer t = js::Tokenizer(test.code);
        auto p = js::Parser(t);
        std::shared_ptr<js::Program> program;
        js::Interpreter interpreter;
        js::Value result = js::Value(js::Value::UNDEFINED, "");

        try {
            program = p.parse_program();
            result = interpreter.run(program);
        } catch (js::SyntaxError e) {
            std::cerr << "TEST FAILED: " << test.code << std::endl << e.message << std::endl;
            throw test_error{};
        }

        // program->dump(0);

        assert(test.result_type, result.get_type(), test.code);
        assert(test.result_value, result.get_value(), test.code);

        std::cout << "PASSED: " << test.code << std::endl;
    }
}

}

#endif
