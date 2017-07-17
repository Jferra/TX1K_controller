//
// Created by narvena on 29/06/17.
//

#include "CommunicationManager.h"

CommunicationManager::CommunicationManager() {
    mqtt = new MQTTService(BROKER_ADDRESS, MQTT_CLIENT_ID);
}

CommunicationManager::~CommunicationManager(){}

void CommunicationManager::startCommunicationManager()
{
    // Open sockets
    colorSocket = startColorSocket();

    // Initialize MQTTService
    mqtt->setCallbacks(NULL, messageArrivedCallback, NULL);
    mqtt->connect();

    // Subscribe to topic
    mqtt->subscribeToTopic(MQTT_TOPIC, QOS);
}

int CommunicationManager::startColorSocket(){
    int socket = NetworkService::openSocket(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);
    return socket;
}

int CommunicationManager::startButtonSocket(){
    //todo
    //int socket = openSocket();
    return 0;
}

int CommunicationManager::messageArrivedCallback(void *context, char* topicName, int topicLen, MQTTClient_message *message){
    char* payloadptr;
    int hasMessageArrived;
    //payloadptr = message->payload; //todo this is to correct

    /*for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');*/

    std::cout << "Message received on topic" << topicName << " !" << std::endl;
    std::cout << payloadptr << std::endl;

    //todo send message to color thread
    hasMessageArrived = NetworkService::sendMessageToSocket(colorSocket, payloadptr);


    // Free memory allocated to the message once it is processed
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return hasMessageArrived;
}

/*
void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();*/