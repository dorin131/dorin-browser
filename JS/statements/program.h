#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

#include "block_statement.h"

namespace js {

/**
 * @brief Is the topmost node in the AST
 */
class Program: public BlockStatement
{
public:
    Program();

    // Overrides
    void dump(int indent) override;
    inline std::string get_type() override { return "Program"; };
};

} // namespace js

#endif // PROGRAM_H
