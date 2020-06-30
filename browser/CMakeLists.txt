add_executable (browser main.cpp)

target_link_libraries (browser LINK_PUBLIC JS)
target_link_libraries (browser -lX11)

enable_testing()