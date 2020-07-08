#include "display.h"

namespace gui {

DDisplay::DDisplay()
{
    this->display = XOpenDisplay(0);

    if (!this->display) {
        std::cerr << "Failed to open display\n";
    } else {
        std::cout << "Opened display\n";
    }
}

DDisplay::~DDisplay()
{
    if (this->display) {
        XCloseDisplay(this->display);
        this->display = 0;
        std::cout << "Closed display\n";
    }
}

}
