#include "program.h"

namespace js {

Program::Program()
{

}

void Program::dump(int indent)
{
    std::cout << "Program" << std::endl;
    for (std::shared_ptr<Statement> s : get_elements()) {
        s->dump(indent + 1);
    }
};

} // namespace js
