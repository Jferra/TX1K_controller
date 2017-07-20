#include <iostream>
#include <thread>
#include <wiringPi.h>
#include "CommunicationManager.h"
#include "color.h"
#include "button.h"

int main() {
    CommunicationManager * cM = new CommunicationManager;

    //todo start color & button sockets

    std::cout << "Setting up GPIOs" << std::endl;
    wiringPiSetup();    // Setup Pins using wiringPi mapping

    std::thread communicationThread(std::bind(&CommunicationManager::startCommunicationManager, cM));
    std::thread colorThread(setupColorThread);
    std::thread buttonThread(setupButtonThread);

    communicationThread.join();
    colorThread.join();
    buttonThread.join();

    delete cM;
    return 0;
}