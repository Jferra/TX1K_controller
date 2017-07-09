//
// Created by narvena on 29/06/17.
//

#include "CommunicationManager.h"

void startCommunicationManager(){
    // Open sockets
    int colorSocket = startColorSocket();
    int buttonSocket;

    // Subscribe to MQTT topic
    //MQTTService mqtt = new MQTTService(BROKER_ADDRESS, MQTT_CLIENT_ID);

}

void startColorSocket(){
    int socket = openSocket(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);
    return socket;
}

void startButtonSocket(){
    //todo
    //int socket = openSocket();
}

/*
void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();*/