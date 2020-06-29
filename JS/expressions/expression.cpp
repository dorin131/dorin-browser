#include "expression.h"

namespace js {

Expression::Expression()
{

}

void Expression::dump(int indent)
{
    print_indent(indent);
    std::cout << "Expression" << std::endl;
};

} // namespace js
