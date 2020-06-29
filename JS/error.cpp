#include "error.h"

namespace js {

SyntaxError::SyntaxError()
{
    message = "Unknown";
}

SyntaxError::SyntaxError(std::string msg): message(msg)
{

}

} // namespace js
