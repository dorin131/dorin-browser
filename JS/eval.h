#ifndef EVAL_H
#define EVAL_H

#include <string>
#include <iostream>
#include "value.h"
#include "interpreter.h"
#include "tokenizer.h"
#include "parser.h"

namespace js {

class Eval
{
public:
    Eval();

    Value run(std::string);
    void enable_debug();
private:
    bool debug = false;
};

}

#endif