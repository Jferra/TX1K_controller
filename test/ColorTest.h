//
// Created by joelle.ferrari on 23/08/2017.
//

#ifndef CONTROLLER_COLORTEST_H
#define CONTROLLER_COLORTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ColorTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( ColorTest );
    CPPUNIT_TEST( testColorMessageConversion );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    void testColorMessageConversion();
};

#endif //CONTROLLER_COLORTEST_H
