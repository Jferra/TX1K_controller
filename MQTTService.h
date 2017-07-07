//
// Created by narvena on 22/06/17.
//

#ifndef CONTROLLER_MQTTSERVICE_H
#define CONTROLLER_MQTTSERVICE_H

#include <cstdlib>
#include <cstring>
#include <MQTTClient.h>

#define ADDRESS     "tcp://37.187.245.213:1883"
//#define CLIENTID    "ExampleClientPub"
//#define TOPIC       "test"
#define QOS         0
#define TIMEOUT     10000L

class MQTTService {

public:
    MQTTClient client;
    MQTTClient_connectOptions conn_opts;
    MQTTClient_message pubmsg;
    MQTTClient_deliveryToken token;
    char* clientID;
    int retCode;


    MQTTService(
            MQTTClient_connectOptions pConnectOptions,
            MQTTClient_message pMessage,
            MQTTClient_deliveryToken pToken,
            char* clientID);

    void initMQTTClient();

    void sendMessageToTopic(char* pTopic, char* pMessage);

    void subscribeToTopic(char* pTopic);

    void disconnectClient();
};


#endif //CONTROLLER_MQTTSERVICE_H
