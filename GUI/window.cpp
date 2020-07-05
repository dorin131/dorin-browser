#include "window.h"

namespace gui {

DWindow::DWindow()
{

}

void DWindow::draw_window()
{
    // Create the window
    Window w = XCreateWindow(display, DefaultRootWindow(display), 0, 0, 200,
                200, 0, CopyFromParent, CopyFromParent, CopyFromParent, 0, 0);

    // Show the window
    XMapWindow(display, w);
    XFlush(display);

    XEvent event;

    for (;;)
    {
        XNextEvent(display, &event);

        if (event.type == KeyPress)
            break;
    }
}

}
