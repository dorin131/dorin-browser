#include "tests.h"
#include "interpreter.cpp"

int main()
{
    try {
        tests::interpreter_tests();
        std::cout << "TESTS PASSED\n";
    } catch (test_error e) {
        std::cerr << "TEST FAILED: " << e.msg << std::endl;
        std::cerr << "TESTS FAILED\n";
    }
}