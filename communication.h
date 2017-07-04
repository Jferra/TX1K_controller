//
// Created by narvena on 29/06/17.
//

#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

void startCommunicationThread();

void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();

#endif //CONTROLLER_COMMUNICATION_H
