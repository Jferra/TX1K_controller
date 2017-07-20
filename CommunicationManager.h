//
// Created by narvena on 29/06/17.
//

#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "NetworkService.h"
#include "MQTTService.h"

#define BROKER_ADDRESS "tcp://37.187.245.213:1883"
#define MQTT_CLIENT_ID "Toto"
#define MQTT_TOPIC     "toto"
#define QOS            0

#define COLOR_SOCKET_ADR    "127.0.0.1"
#define COLOR_SOCKET_PORT   45000

class CommunicationManager{

public:
    MQTTService * mqtt;
    int colorSocket;
    int buttonSocket;

    CommunicationManager();
    virtual ~CommunicationManager();

    /**
     * Start CommunicationManager
     */
    void startCommunicationManager();

private:
    int startColorSocket();

    int startButtonSocket();

    void sendButtonPressedNotification();

    void sendNewColorSettings();

    void publishOnSocket();

    void publishOnMQTTTopic();
};

#endif //CONTROLLER_COMMUNICATION_H
