//
// Created by narvena on 22/06/17.
//

#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

#include <cstdlib>
#include <cstring>
#include <MQTTClient.h>

#define ADDRESS     "tcp://37.187.245.213:1883"
//#define CLIENTID    "ExampleClientPub"
//#define TOPIC       "test"
#define QOS         0
#define TIMEOUT     10000L

class Communication {

public:
    MQTTClient client;
    MQTTClient_connectOptions conn_opts;
    MQTTClient_message pubmsg;
    MQTTClient_deliveryToken token;
    char* clientID;
    int retCode;


    Communication(
            MQTTClient_connectOptions pConnectOptions,
            MQTTClient_message pMessage,
            MQTTClient_deliveryToken pToken,
            char* clientID);

    void initMQTTClient();

    void disconnectClient();

    void sendMessageToTopic(char* pTopic, char* pMessage);
};


#endif //CONTROLLER_COMMUNICATION_H
