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
#include "NetworkService.h"
#include "MQTTService.h"


/**
 * Start CommunicationManager
 */
void startCommunicationManager();

void startColorSocket();

void startButtonSocket();

void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();

#endif //CONTROLLER_COMMUNICATION_H
