cmake_minimum_required(VERSION 3.5)
project(Controller)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        color.cpp
        color.h
        button.cpp
        button.h
        Communication.cpp
        Communication.h)

add_executable(Controller ${SOURCE_FILES})
target_link_libraries(Controller /usr/local/lib/libwiringPi.so)
target_link_libraries(Controller /usr/local/lib/libpaho-mqtt3c.so)
