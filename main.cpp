#include <iostream>
#include <wiringPi.h>
#include "color.h"
#include "button.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    wiringPiSetupGpio();

    setupColorThread();

    setupButtonThread();

    return 0;
}