#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <unistd.h>

#include "display.h"
#include "painter.h"

namespace gui {

class MainWindow
{
public:
    MainWindow(int width, int height);
    ~MainWindow();

    void show();
    inline Display* get_display() { return this->display; };
    inline Window get_window() { return this->window; };
    inline int get_window_id() { return this->window_id; };
private:
    void hide();

    const char* window_title = "Dorin Browser";
    const int window_id = 0;
    DisplayWrap display_wrap = DisplayWrap(window_id);
    Display* display = display_wrap.get_display();
    Window window;
    int width;
    int height;
};

}

#endif // WINDOW_H
