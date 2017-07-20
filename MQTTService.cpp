//
// Created by narvena on 22/06/17.
//

#include "MQTTService.h"

volatile MQTTClient_deliveryToken deliveredToken;

MQTTService::MQTTService(char* brokerAddress, char* pClientID)
{
    conn_opts = MQTTClient_connectOptions_initializer;
    pubmsg = MQTTClient_message_initializer;
    //token = pToken;
    clientID = pClientID;

    initMQTTClient(brokerAddress);

    // Set MQTTClient callbacks
    MQTTClient_setCallbacks(client, NULL, connectionLost, messageArrivedCallback, delivered);
};

MQTTService::~MQTTService(){}

void MQTTService::initMQTTClient(char* brokerAddress) {
    MQTTClient_create(&client, brokerAddress, clientID,
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
}

void MQTTService::connect() {
    if ((retCode = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", retCode);
        exit(EXIT_FAILURE);
    }
}


void MQTTService::subscribeToTopic(char* pTopic, int pQos){
    MQTTClient_subscribe(client, pTopic, pQos);
}

void MQTTService::sendMessageToTopic(char* pTopic, char* pMessage, int pQos) {
    pubmsg.payload = &pMessage;
    pubmsg.payloadlen = strlen(pMessage);
    pubmsg.qos = pQos;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, pTopic, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
                   "on topic %s for client with ClientID: %s\n",
           (int)(TIMEOUT/1000), pMessage, pTopic, clientID);
    retCode = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    disconnectClient();
}

void MQTTService::unsubscribeFromTopic(char* pTopic){
    MQTTClient_unsubscribe(clientID, pTopic);
}

void MQTTService::disconnectClient() {
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}


void MQTTService::delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredToken = dt;
}

int MQTTService::messageArrivedCallback(void *context, char* topicName, int topicLen, MQTTClient_message *message)
{
    void* payloadptr;
    int hasMessageArrived;
    //payloadptr = message->payload; //todo this is to correct

    std::cout << "Message received on topic" << topicName << " !" << std::endl;
    std::cout << payloadptr << std::endl;

    //todo send message to color thread (must be done in CommunicationManager
    //hasMessageArrived = NetworkService::sendMessageToSocket(colorSocket, payloadptr);


    // Free memory allocated to the message once it is processed
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return hasMessageArrived;   //todo return message. Needs to be changed, as message has been cleaned just before
}

/*int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;

    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}*/

void MQTTService::connectionLost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}