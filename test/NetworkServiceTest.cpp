//
// Created by joelle.ferrari on 22/08/2017.
//
#include "NetworkServiceTest.h"
#include "NetworkService.h"

// Register fixture into the registry
CPPUNIT_TEST_SUITE_REGISTRATION( NetworkServiceTest );

void NetworkServiceTest::setUp()
{
}
void NetworkServiceTest::tearDown()
{

}
void NetworkServiceTest::testSocketMessageReception()
{
    const int testSocketPort = 46666;
    const char* testSocketAddr = "127.0.0.1";

    int socketFd;

    const char * messageToSend = "1,2,3,4";
    socketFd = NetworkService::openSocket(testSocketPort, testSocketAddr);

    CPPUNIT_ASSERT(socketFd != 0);





    CPPUNIT_FAIL( "not implemented :)" );
}
