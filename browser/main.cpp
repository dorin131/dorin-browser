#include <unistd.h>
#include <iostream>
#include "../JS/eval.h"
#include "../GUI/window.h"

int main(int, char**) {
    js::Eval().run("var x = 1+2; x;").get_value();
    auto window = gui::MainWindow(500, 500);
    window.show();
    auto painter = gui::Painter(window.get_display(), window.get_window(), window.get_window_id());
    painter.start();
}
