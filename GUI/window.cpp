#include "window.h"

namespace gui {

DWindow::DWindow()
{

}

void DWindow::draw_window(int width, int height)
{
    // Create the window
    Window window = XCreateWindow(display, DefaultRootWindow(display), 0, 0, width,
                height, 0, CopyFromParent, CopyFromParent, CopyFromParent, 0, 0);

    // Show the window
    XMapWindow(display, window);
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
