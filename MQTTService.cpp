//
// Created by narvena on 22/06/17.
//

#include "MQTTService.h"

MQTTService::MQTTService(
        MQTTClient_connectOptions pConnectOptions,
        MQTTClient_message pMessage,
        MQTTClient_deliveryToken pToken,
        char* pClientID)
{
    MQTTClient client;
    conn_opts = MQTTClient_connectOptions_initializer;
    pubmsg = MQTTClient_message_initializer;
    token = pToken;
    clientID = pClientID;

    initMQTTClient();
};

void MQTTService::initMQTTClient() {
    MQTTClient_create(&client, ADDRESS, clientID,
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((retCode = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", retCode);
        exit(EXIT_FAILURE);
    }
}

void MQTTService::sendMessageToTopic(char* pTopic, char* pMessage) {
    pubmsg.payload = &pMessage;
    pubmsg.payloadlen = strlen(pMessage);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, pTopic, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
                   "on topic %s for client with ClientID: %s\n",
           (int)(TIMEOUT/1000), pMessage, pTopic, clientID);
    retCode = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    disconnectClient();
}

void MQTTService::subscribeToTopic(char* pTopic){

}

void MQTTService::disconnectClient() {
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}