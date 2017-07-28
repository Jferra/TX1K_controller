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

const std::string BROKER_ADDRESS("tcp://37.187.245.213:1883");
const std::string MQTT_CLIENT_ID("Toto");
const int	N_RETRY_ATTEMPTS = 5;

#define TIMEOUT     10000L

#define COLOR_SOCKET_ADR    "127.0.0.1"
#define COLOR_SOCKET_PORT   45000


class MQTTService {

public:
    mqtt::async_client client;
    mqtt::connect_options connOpts;

    //MQTTClient_message pubmsg;
    //MQTTClient_deliveryToken token;
    char* clientID;
    int retCode;

    int colorSocketFileDescriptor;
    int buttonSocketFileDescriptor;

    int isClientConnected = false;

    /**
     * MQTTService Constructor
     * @method MQTTService
     */
    //MQTTService(char* brokerAddress, char* pClientID);
    MQTTService();
    virtual ~MQTTService();

    void startMQTTServiceThread();

    void openColorSocketServer(unsigned int pPort, char* pIp);
    void openButtonSocketServer(unsigned int pPort, char* pIp);

    /**
     * Initializes the MQTT Client and connects it to the given broker
     * @method initMQTTClient
     */
    void initMQTTClient();
    //void initMQTTClient(char* brokerAddress);

    /**
     * Attempt to connect client to MQTT Broker
     * @method connectClient
     * @return void
     */
    void connectClient();

    void disconnectClient();

    void sendMessageToTopic(const std::string pTopic, char* pMessage, const int pQos);

    /*void subscribeToTopic(char* pTopic, int pQos);

    void unsubscribeFromTopic(char* pTopic);


    static void delivered(void *context, MQTTClient_deliveryToken dt);

    static int messageArrivedCallback(void *context, char* topicName, int topicLen, MQTTClient_message *message);

    static void connectionLost(void *context, char *cause);*/
};


#endif //CONTROLLER_MQTTSERVICE_H
