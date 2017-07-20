//
// Created by narvena on 29/06/17.
//

#include "CommunicationManager.h"

CommunicationManager::CommunicationManager() {
    mqtt = new MQTTService(BROKER_ADDRESS, MQTT_CLIENT_ID);
}

CommunicationManager::~CommunicationManager(){
    delete mqtt;
}

void CommunicationManager::startCommunicationManager()
{
    // Open sockets
    colorSocket = startColorSocket();

    // Initialize MQTTService
    /*mqtt->connect();

    // Subscribe to topic
    mqtt->subscribeToTopic(MQTT_TOPIC, QOS);*/
}

int CommunicationManager::startColorSocket()
{
    int socket = NetworkService::openSocket(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);
    return socket;
}

int CommunicationManager::startButtonSocket()
{
    //todo
    //int socket = openSocket();
    return 0;
}

/*
void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();*/