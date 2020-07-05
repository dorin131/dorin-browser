#include <unistd.h>
#include <iostream>
#include "../JS/eval.h"
#include "../GUI/window.h"

int main(int, char**) {
    js::Eval().run("var x = 1+2; x;").get_value();
    gui::DWindow().draw_window(500, 500);
}
