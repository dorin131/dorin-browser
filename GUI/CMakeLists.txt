add_library (GUI
    window.h
    window.cpp
    display.h
    display.cpp
)

target_include_directories (GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries (GUI LINK_PUBLIC -lX11)
