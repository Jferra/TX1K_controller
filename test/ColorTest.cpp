//
// Created by joelle.ferrari on 23/08/2017.
//

#include "ColorTest.h"

#include "color.h"

void ColorTest::setUp()
{

}
void ColorTest::tearDown(){}

void ColorTest::testColorMessageConversion()
{
    char messageReceived[256] = "1,2,3,4";
    std::vector<std::string> messageVectorExpected = {"1", "2", "3", "4"};
    int msgConvertedToIntExpected[4] = {1,2,3,4};

    std::vector<std::string> conversionInVector = split(messageReceived, ',');
    CPPUNIT_ASSERT(conversionInVector == messageVectorExpected);

    std::string * array = &conversionInVector[0];

    int intColors[4];
    getIntColors(array, intColors);
    CPPUNIT_ASSERT(intColors == msgConvertedToIntExpected);
}