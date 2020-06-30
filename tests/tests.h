#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>

struct test_error {
    std::string msg;
};

#define ASSERT(n, expr) \
    if (!(expr)) {\
        throw test_error{n};\
    };\

#endif