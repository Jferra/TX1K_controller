#include <iostream>
#include <thread>
#include <wiringPi.h>
#include "color.h"
#include "button.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    //todo start color & button sockets

    std::cout << "Setting up GPIO" << std::endl;
    wiringPiSetup();    // Setup Pins using wiringPi mapping

    std::thread colorThread(setupColorThread);
    std::thread buttonThread(setupButtonThread);
    //std::thread communicationThread()

    colorThread.join();
    buttonThread.join();

    return 0;
}