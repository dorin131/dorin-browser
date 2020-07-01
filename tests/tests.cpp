#include "tests.h"
#include "interpreter.h"

int main()
{
    try {
        tests::interpreter_tests();
        std::cout << "TESTS PASSED\n";
    } catch (tests::test_error e) {
        std::cerr << "TEST FAILED: " << e.msg << std::endl;
        std::cerr << "TESTS FAILED\n";
    }
    return 0;
}
