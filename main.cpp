#include <iostream>
#include <wiringPi.h>
#include "color.h"
#include "button.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    wiringPiSetupGpio();
    std::cout << "Setting up GPIO" << std::endl;

    setupColorThread();

    //setupButtonThread();

    return 0;
}