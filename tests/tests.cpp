#include "tests.h"

#include "interpreter.cpp"

int main()
{
    try {
        interpreter_tests();
        std::cout << "TESTS PASSED\n";
    } catch (test_error e) {
        std::cerr << "TESTS FAILED\n";
    }
}