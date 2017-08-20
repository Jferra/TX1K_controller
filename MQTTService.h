//
// Created by narvena on 22/06/17.
//

#ifndef CONTROLLER_MQTTSERVICE_H
#define CONTROLLER_MQTTSERVICE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include "json/json.h"
extern "C" {
    #include <cstdlib>
    #include <cstring>
    #include <cctype>
    //#include <MQTTClient.h>
}
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include "mqtt/async_client.h"
#include "Utils.h"
#include "NetworkService.h"
#include "MQTTCallback.h"

#define BUTTON_PRESSED (0)
#define SET_COLORS (1)

const char * const BROKER_ADDRESS = "tcp://37.187.245.213:1883";

#define TIMEOUT     10000L

const char * const COLOR_SOCKET_ADR = "127.0.0.1";
#define COLOR_SOCKET_PORT   45003


class MQTTService {

public:
    mqtt::async_client_ptr async_client_ptr;
    mqtt::connect_options connOpts;
    mqtt::token_ptr connection_token;
    callback * m_callback;

    char* clientID;
    int retCode;

    int colorSocketFileDescriptor;
    int buttonSocketFileDescriptor;

    bool isMQTTClientConnected = false;

    /**
     * MQTTService Constructor
     * @method MQTTService
     */
    //MQTTService(char* brokerAddress, char* pClientID);
    MQTTService();
    virtual ~MQTTService();

    void startMQTTServiceThread();

    void openColorSocketServer(unsigned int pPort, const char* pIp);
    void openButtonSocketServer(unsigned int pPort, const char* pIp);

    /**
     * Initializes the MQTT Client and connects it to the given broker
     * @method initMQTTClient
     */
    void initMQTTClient();

    /**
     * Attempt to connect client to MQTT Broker
     * @method connectClient
     * @return void
     */
    void connectClient();

    void disconnectClient();

    void sendMessageToTopic(const std::string pTopic, char* pMessage, const int pQos);

    void subscribeToTopic(const std::string pTopic, const int pQos);

};


#endif //CONTROLLER_MQTTSERVICE_H
