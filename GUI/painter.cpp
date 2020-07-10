#include "painter.h"

namespace gui {

Painter::Painter(Display* d, Window w, int id): display(d), window(w), window_id(id)
{
    XGCValues values;
    unsigned long valuemask = 0;
    this->gc = XCreateGC(this->display, this->window, valuemask, &values);

    XSetForeground(this->display, this->gc, BlackPixel(this->display, this->window_id));
}

void Painter::start()
{
    running = true;
    XEvent event;
    while (running) {
        XNextEvent(this->display, &event);
        handle_event(&event);
    }
}

void Painter::handle_event(XEvent* event)
{
    switch (event->type) {
    case Expose:
        XDrawLine(this->display, this->window, gc, 0, 0, 100, 100);
        break;
    case ButtonPress:
        this->running = false;
        break;
    }
}

}
