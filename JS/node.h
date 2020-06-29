#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>

#include "value.h"

namespace js {

// Forward declarations
class Interpreter;

class Node
{
public:
    Node();
    virtual ~Node();

    virtual std::string get_type() = 0;
    virtual void dump(int indent) = 0;
    virtual Value execute(Interpreter&) = 0;
protected:
    inline void print_indent(int n) {
        for (int i = n; i < n * 3; i++) std::cout << " ";
    };
};

} // namespace js

#endif // NODE_H
