//
// Created by joelle.ferrari on 22/08/2017.
//

#ifndef CONTROLLER_NETWORKSERVICETEST_H
#define CONTROLLER_NETWORKSERVICETEST_H

#include <cppunit/extensions/HelperMacros.h>

class NetworkServiceTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( NetworkServiceTest );
    CPPUNIT_TEST( testSocketMessageReception );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    void testSocketMessageReception();
};

#endif //CONTROLLER_NETWORKSERVICETEST_H
