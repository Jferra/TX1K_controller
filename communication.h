//
// Created by narvena on 29/06/17.
//

#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//htons -> this writes the port number in network byte order
#define COLOR_SOCKET_PORT htons(45000)
#define COLOR_SOCKET_ADR inet_addr("127.0.0.1")

void errorInSocket(const char *msg);

void startCommunicationThread();

void startSockets();

void startColorSocket();

void startButtonSocket();

void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();

#endif //CONTROLLER_COMMUNICATION_H
