#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <display.h>
#include <unistd.h>

namespace gui {

class DWindow
{
public:
    DWindow();

    void draw_window(int w, int h);  
};

}

#endif // WINDOW_H
