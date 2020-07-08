#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <X11/Xlib.h>

namespace gui {

class DDisplay
{
public:
    DDisplay();
    ~DDisplay();

    inline Display* get() { return this->display; };
private:
    Display* display;
};

}

#endif // DISPLAY_H
