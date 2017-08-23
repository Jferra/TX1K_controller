#include <iostream>
#include <thread>
#include <wiringPi.h>
#include "MQTTService.h"
#include "color.h"
#include "button.h"

int main() {
    MQTTService * mqttService = new MQTTService();

    std::cout << "MAIN PROGRAM --- Setting up GPIOs" << std::endl;
    wiringPiSetup();    // Setup Pins using wiringPi mapping

    std::thread colorThread(setupColorThread);
    std::thread buttonThread(setupButtonThread);
    std::thread mqttServiceThread(std::bind(&MQTTService::startMQTTServiceThread, mqttService));

    colorThread.join();
    buttonThread.join();
    mqttServiceThread.join();


    delete mqttService;
    return 0;
}