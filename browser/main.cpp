#include <X11/Xlib.h>
#include <unistd.h>
#include <iostream>
#include "../JS/test.cpp"
#include "../JS/tokenizer.h"
#include "../JS/parser.h"
#include "../JS/error.h"

std::string eval_js(std::string code)
{
    js::Tokenizer t = js::Tokenizer(code);
    auto p = js::Parser(t);
    std::shared_ptr<js::Program> program;
    try {
        program = p.parse_program();
    } catch (js::SyntaxError e) {
        return "Syntax error: " + e.message;
    }
    js::Interpreter interpreter;
    auto result = interpreter.run(program);

    return result.get_value();
}

void draw_window()
{
    // Open a display.
    Display *d = XOpenDisplay(0);

    if ( d )
    {
      // Create the window
      Window w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 200,
			       100, 0, CopyFromParent, CopyFromParent,
			       CopyFromParent, 0, 0);

      // Show the window
      XMapWindow(d, w);
      XFlush(d);

      // Sleep long enough to see the window.
      sleep(10);
    }
}

int main(int, char**) {
    eval_js("var x = 1+2; x;");
    draw_window();
}
