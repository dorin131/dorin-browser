#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <X11/Xlib.h>

namespace gui {

class DisplayWrap
{
public:
    DisplayWrap(int id);
    ~DisplayWrap();

    inline Display* get_display() { return this->display; };
    inline int get_id() { return id; };
private:
    Display* display;
    int id;
};

}

#endif // DISPLAY_H
