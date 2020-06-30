add_executable(tests
    tests.h
    tests.cpp
)

target_link_libraries (tests LINK_PUBLIC JS)

add_test(NAME AllTests COMMAND tests)