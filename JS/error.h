#ifndef ERROR_H
#define ERROR_H

#include <iostream>

namespace js {

class SyntaxError
{
public:
    SyntaxError();
    SyntaxError(std::string);
    std::string message;
};

} // namespace js

#endif // ERROR_H
