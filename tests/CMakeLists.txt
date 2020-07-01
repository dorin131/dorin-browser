add_executable(tests
    tests.h
    tests.cpp
    interpreter.h
)

target_link_libraries (tests LINK_PUBLIC JS)

add_test(NAME AllTests COMMAND tests)