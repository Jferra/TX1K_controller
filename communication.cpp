//
// Created by narvena on 29/06/17.
//

#include "communication.h"

void errorInSocket(const char *msg) {
    perror(msg);
    exit(0);
}

void startCommunicationThread(){

    //todo subscribe to ColorSocket
    startColorSocket();
    //todo subscribe to ButtonSocket
    //todo subscribe to MQTT /id/mobile topic
    //todo init MQTTClient
}


void startSockets(){
    startColorSocket();
    startButtonSocket();
}

void startColorSocket(){
    int sockfd, newsockfd, n;
    socklen_t clilen;   // socket lenght
    char buffer[256]; //reception buffer
    sockaddr_in serverAddr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET; //AF_INET -> to use inter-network connection (UDp, TCP)
    serverAddr.sin_port = COLOR_SOCKET_PORT;
    serverAddr.sin_addr.s_addr = COLOR_SOCKET_ADR;  //IP address
    if (bind(sockfd, (struct sockaddr *) &serverAddr,
             sizeof(serverAddr)) < 0)    // binds the socket to its port
        errorInSocket("ERROR on binding");
    listen(sockfd,5); //5 = liste d'attente pour accepter connexion
    clilen = sizeof(cli_addr);
    // Accept first connection
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);    // allocation of client address memory needed

    //this is to put in an infinite loop -> writes a message when asked
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) errorInSocket("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);

    bzero(buffer,256);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) errorInSocket("ERROR writing to socket");

    close(newsockfd);
    close(sockfd);
}

void startButtonSocket(){
    int sockfd, newsockfd, n;
    socklen_t clilen;   // socket length
    char buffer[256]; //reception buffer
    sockaddr_in serverAddr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET; //AF_INET -> to use inter-network connection (UDp, TCP)
    serverAddr.sin_port = COLOR_SOCKET_PORT;
    serverAddr.sin_addr.s_addr = COLOR_SOCKET_ADR;  //IP address
    if (bind(sockfd, (struct sockaddr *) &serverAddr,
             sizeof(serverAddr)) < 0)
        errorInSocket("ERROR on binding");
    listen(sockfd,5); //5 = liste d'attente pour accepter connexion
    clilen = sizeof(cli_addr);
    // Accept first connection
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);    // allocation of client address memory needed



    //this is to put in an infinite loop -> reads message whenever one is received
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) errorInSocket("ERROR reading from socket");
}

/*
void sendButtonPressedNotification();

void sendNewColorSettings();

void publishOnSocket();

void publishOnMQTTTopic();*/