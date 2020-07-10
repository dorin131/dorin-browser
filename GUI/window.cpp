#include "window.h"

namespace gui {

MainWindow::MainWindow(int w, int h)
    : width(w), height(h)
{
    const int border_width = 1;
    const int x = 0;
    const int y = 0;

    // Create window
    this->window = XCreateSimpleWindow(this->display,
                                       RootWindow(this->display, this->window_id),
                                       x, y, this->width, this->height, border_width,
                                       BlackPixel(this->display, this->window_id),
                                       WhitePixel(this->display, this->window_id));
    // Set window title
    XStoreName(this->display, this->window, this->window_title);
}

MainWindow::~MainWindow()
{
    hide();
    if (this->window) {
        XDestroyWindow(this->display, this->window);
    }
}

void MainWindow::show()
{
    XSelectInput(this->display, this->window, ButtonPressMask|ExposureMask);
    XMapWindow(this->display, this->window);
    XFlush(this->display);
}

void MainWindow::hide()
{
    XUnmapWindow(this->display, this->window);
    XFlush(this->display);
}

}
