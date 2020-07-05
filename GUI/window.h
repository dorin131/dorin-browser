#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>

namespace gui {

class DWindow
{
public:
    DWindow();

    void draw_window(int w, int h);
private:
    Display* display = XOpenDisplay(0);
};

}

#endif // WINDOW_H