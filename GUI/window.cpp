#include "window.h"

namespace gui {

DWindow::DWindow()
{

}

void DWindow::draw_window(int width, int height)
{
    // Attributes
    XSetWindowAttributes attr;
    attr.background_pixel = XWhitePixel(display, 0);

    // Create the window
    Window window = XCreateWindow(display, DefaultRootWindow(display), 0, 0, width,
                height, 0, CopyFromParent, CopyFromParent, CopyFromParent, CWBackPixel, &attr);

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
