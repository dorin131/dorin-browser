#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>

namespace tests {

struct test_error {
    std::string msg;
};

template<typename T>
void assert(T expected, T received, std::string msg = "")
{
    if (expected != received) {
        std::cerr << "EXPECTED: " << expected << " RECEIVED: " << received << std::endl;
        throw test_error{msg};
    }
}

}

#endif