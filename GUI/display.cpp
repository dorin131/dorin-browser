#include "display.h"

namespace gui {

DisplayWrap::DisplayWrap(int id): id(id)
{
    this->display = XOpenDisplay(NULL);

    if (!this->display) {
        std::cerr << "Failed to open display\n";
    } else {
        std::cout << "Opened display\n";
    }
}

DisplayWrap::~DisplayWrap()
{
    if (this->display) {
        XCloseDisplay(this->display);
        this->display = 0;
        std::cout << "Closed display\n";
    }
}

}
