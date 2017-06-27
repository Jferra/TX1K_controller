#include <iostream>
#include <wiringPi.h>
#include "color.h"
#include "button.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << "Setting up GPIO" << std::endl;
    wiringPiSetup();    // Setup Pins using wiringPi mapping

    setupColorThread();

    //setupButtonThread();

    return 0;
}