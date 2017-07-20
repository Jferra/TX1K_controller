//
// Created by narvena on 22/06/17.
//

#ifndef CONTROLLER_MQTTSERVICE_H
#define CONTROLLER_MQTTSERVICE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <functional>
extern "C" {
    #include <cstdlib>
    #include <cstring>
    #include <MQTTClient.h>
}
#include "NetworkService.h"

#define TIMEOUT     10000L

class MQTTService {

public:
    MQTTClient client;
    MQTTClient_connectOptions conn_opts;
    MQTTClient_message pubmsg;
    MQTTClient_deliveryToken token;
    char* clientID;
    int retCode;

    MQTTService(char* brokerAddress, char* pClientID);

    virtual ~MQTTService();

    void initMQTTClient(char* brokerAddress);

    void connect();

    void sendMessageToTopic(char* pTopic, char* pMessage, int pQos);

    void subscribeToTopic(char* pTopic, int pQos);

    void unsubscribeFromTopic(char* pTopic);

    void disconnectClient();

    static void delivered(void *context, MQTTClient_deliveryToken dt);

    static int messageArrivedCallback(void *context, char* topicName, int topicLen, MQTTClient_message *message);

    static void connectionLost(void *context, char *cause);
};


#endif //CONTROLLER_MQTTSERVICE_H
