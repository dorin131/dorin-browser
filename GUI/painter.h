#ifndef PAINTER_H
#define PAINTER_H

#include <X11/Xlib.h>
#include <iostream>

#include "display.h"

namespace gui {

class Painter
{
public:
    Painter(Display* display, Window w, int id);

    void line(int ax, int ay, int bx, int by);
    void start();
private:
    GC gc;
    Display* display;
    Window window;
    int window_id;
    bool running = false;

    void handle_event(XEvent*);
};

}

#endif // PAINTER_H
