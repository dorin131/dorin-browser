#include <X11/Xlib.h>
#include <unistd.h>
#include <iostream>
#include "../JS/eval.h"

std::string eval_js(std::string code)
{
    return js::Eval().run(code).get_value();
}

void draw_window()
{
    // Open a display.
    Display *d = XOpenDisplay(0);

    // Create the window
    Window w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 200,
                200, 0, CopyFromParent, CopyFromParent,
                CopyFromParent, 0, 0);

    // Show the window
    XMapWindow(d, w);
    XFlush(d);

    XEvent event;

    for (;;)
    {
        XNextEvent(d, &event);

        if (event.type == KeyPress)
            break;
    }
}

int main(int, char**) {
    eval_js("var x = 1+2; x;");
    draw_window();
}
