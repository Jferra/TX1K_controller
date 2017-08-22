cmake_minimum_required(VERSION 3.5)
project(Test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set(INCLUDE_DIR ../include)
set(JSONCPP_DIR ${INCLUDE_DIR}/json)
set(SOURCE_DIR ../)
set(TEST_DIR ${SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})
include_directories(${JSONCPP_DIR})
include_directories(${SOURCE_DIR})
include_directories(${TEST_DIR})

set(SOURCE_FILES
        #${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/color.cpp
        ${SOURCE_DIR}/color.h
        ${SOURCE_DIR}/button.cpp
        ${SOURCE_DIR}/button.h
        ${SOURCE_DIR}/MQTTService.cpp
        ${SOURCE_DIR}/MQTTService.h
        ${SOURCE_DIR}/MQTTCallback.cpp
        ${SOURCE_DIR}/MQTTCallback.h
        ${SOURCE_DIR}/MQTTActionListener.cpp
        ${SOURCE_DIR}/MQTTActionListener.h
        ${SOURCE_DIR}/NetworkService.cpp
        ${SOURCE_DIR}/NetworkService.h
        ${SOURCE_DIR}/Utils.cpp
        ${SOURCE_DIR}/Utils.h
        ${JSONCPP_DIR}/json.h
        ${JSONCPP_DIR}/json-forwards.h
        ${INCLUDE_DIR}/jsoncpp.cpp
        ${TEST_DIR}/test.cpp
        ${TEST_DIR}/NetworkServiceTest.h
        ${TEST_DIR}/NetworkServiceTest.cpp)

FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
        ${CPPUNIT_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib/arm-linux-gnueabihf/)
FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunit
        ${CPPUNIT_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib/arm-linux-gnueabihf/)

IF(CPPUNIT_INCLUDE_DIR)
    IF(CPPUNIT_LIBRARY)
        SET(CPPUNIT_FOUND "YES")
        SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})
        SET(CPPUNIT_DEBUG_LIBRARIES ${CPPUNIT_DEBUG_LIBRARY} ${CMAKE_DL_LIBS})
    ELSE (CPPUNIT_LIBRARY)
        IF (CPPUNIT_FIND_REQUIRED)
            MESSAGE(SEND_ERROR "Could not find library CppUnit.")
        ENDIF (CPPUNIT_FIND_REQUIRED)
    ENDIF(CPPUNIT_LIBRARY)
ELSE(CPPUNIT_INCLUDE_DIR)
    IF (CPPUNIT_FIND_REQUIRED)
        MESSAGE(SEND_ERROR "Could not find library CppUnit.")
    ENDIF(CPPUNIT_FIND_REQUIRED)
ENDIF(CPPUNIT_INCLUDE_DIR)

find_package (Threads)

add_executable (Test ${SOURCE_FILES})
target_link_libraries(Test /usr/local/lib/libwiringPi.so)
target_link_libraries(Test /usr/local/lib/libpaho-mqttpp3.so)
target_link_libraries(Test /usr/lib/arm-linux-gnueabihf/libcppunit.so)
target_link_libraries (Test ${CMAKE_THREAD_LIBS_INIT})
