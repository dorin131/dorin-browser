#include "window.h"

namespace gui {

DWindow::DWindow()
{

}

void DWindow::draw_window(int width, int height)
{
    DDisplay display = DDisplay();
    // Attributes
    XSetWindowAttributes attr;
    attr.background_pixel = XWhitePixel(display.get(), 0);

    // Create the window
    Window window = XCreateWindow(display.get(), DefaultRootWindow(display.get()), 0, 0, width,
                height, 0, CopyFromParent, CopyFromParent, CopyFromParent, CWBackPixel, &attr);

    // Show the window
    XMapWindow(display.get(), window);
    XFlush(display.get());

    sleep(2);
}

}
