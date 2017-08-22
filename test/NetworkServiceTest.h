//
// Created by joelle.ferrari on 22/08/2017.
//

#ifndef CONTROLLER_NETWORKSERVICETEST_H
#define CONTROLLER_NETWORKSERVICETEST_H

#include <cppunit/extensions/HelperMacros.h>

class NetworkServiceTest : public CppUnit::TestCase
{
public:
    PseudoTest( std::string name ) : CppUnit::TestCase( name ) {}

    void runTest()
    {
        CPPUNIT_ASSERT( 1 == 1 );
        CPPUNIT_ASSERT( !(1 == 2) );
    }
};

#endif //CONTROLLER_NETWORKSERVICETEST_H
