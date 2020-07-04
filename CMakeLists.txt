cmake_minimum_required(VERSION 3.5)

project(dorin-browser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory (browser)
add_subdirectory (JS)
add_subdirectory (tests)
