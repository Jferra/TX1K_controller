cmake_minimum_required(VERSION 3.5)
project(Controller)

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_DIR include)
set(JSONCPP_DIR ${INCLUDE_DIR}/json)

include_directories(${INCLUDE_DIR})
include_directories(${JSONCPP_DIR})

set(SOURCE_FILES
        main.cpp
        color.cpp
        color.h
        button.cpp
        button.h
        MQTTService.cpp
        MQTTService.h
        MQTTCallback.cpp
        MQTTCallback.h
        MQTTActionListener.cpp
        MQTTActionListener.h
        NetworkService.cpp
        NetworkService.h
        Utils.cpp
        Utils.h
        ${JSONCPP_DIR}/json.h
        ${JSONCPP_DIR}/json-forwards.h
        ${INCLUDE_DIR}/jsoncpp.cpp)

find_package (Threads)

add_executable(Controller ${SOURCE_FILES})
target_link_libraries(Controller /usr/local/lib/libwiringPi.so)
target_link_libraries(Controller /usr/local/lib/libpaho-mqttpp3.so)
target_link_libraries (Controller ${CMAKE_THREAD_LIBS_INIT})