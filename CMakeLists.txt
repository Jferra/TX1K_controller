cmake_minimum_required(VERSION 3.7)
project(Controller)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Communication.cpp Communication.h)
add_executable(Controller ${SOURCE_FILES})
target_link_libraries(Controller /usr/local/lib/libpaho-mqtt3c.so)
