#include <iostream>
#include <thread>
#include <wiringPi.h>
#include "MQTTService.h"
#include "color.h"
#include "button.h"

//
//#define BROKER_ADDRESS "tcp://37.187.245.213:1883"
//#define MQTT_CLIENT_ID "Toto"
//#define MQTT_TOPIC     "toto"
//#define QOS            0
//
//#define COLOR_SOCKET_ADR    "127.0.0.1"
//#define COLOR_SOCKET_PORT   45000

int main() {
    //MQTTService * mqttService = new MQTTService(BROKER_ADDRESS, MQTT_CLIENT_ID);
    MQTTService * mqttService = new MQTTService();

    std::cout << "Setting up GPIOs" << std::endl;
    wiringPiSetup();    // Setup Pins using wiringPi mapping

    //std::thread colorThread(setupColorThread);
    //std::thread buttonThread(setupButtonThread);
    std::thread mqttServiceThread(std::bind(&MQTTService::startMQTTServiceThread, mqttService));

    //colorThread.join();
    //buttonThread.join();
    mqttServiceThread.join();
//
//    mqttService->openColorSocketServer(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);
//
//    // Initialize MQTTService
//    mqttService->connect();
//
//    // Subscribe to topic
//    mqttService->subscribeToTopic(MQTT_TOPIC, QOS);
//
//    char* messageToSend = "{\"type\" : \"1\", \"data\" : \"KALIMBA\"}\n";
//
//    mqttService->sendMessageToTopic(MQTT_TOPIC, messageToSend, QOS);

    delete mqttService;
    return 0;
}