#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>

struct test_error {
    std::string name;
};

#define ASSERT(n, expr) \
    try {\
        if (!(expr)) {\
            throw test_error{n};\
        };\
    } catch (test_error e) {\
        std::cerr << "FAILED: " << e.name << std::endl;\
        throw e;\
    }\

#endif