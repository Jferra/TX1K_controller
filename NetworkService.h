//
// Created by narvena on 09/07/17.
//

#ifndef CONTROLLER_NETWORKSERVICE_H
#define CONTROLLER_NETWORKSERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/**
 * Error handler, logs an error message and exits program.
 * @method error
 * @param msg
 */
void error(const char *msg);

/**
 * Connect client to a socket
 * @method connectToSocket
 * @param port  Socket port number
 * @param ip    Socket IP
 * @return socketFileDescriptor
 */
static int connectToSocket(unsigned int port, char* ip);

/**
 * Close client connection from a socket
 * @param socketFileDescriptor
 * @return
 */
static int closeConnectionToSocket(int socketFileDescriptor);

/**
 * Open a socket on a given IP and port
 * @method openSocket
 * @param port  Socket port number
 * @param ip    Socket IP
 * @return
 */
static int openSocket(unsigned int port, char* ip);

/**
 * Close the socket
 * @method closeSocket
 * @param socketFileDescriptor
 * @return
 */
static int closeSocket(int socketFileDescriptor);

/**
 * Send a message trough the socket
 * @method sendMessageToSocket
 * @param socketFd  Socket File descriptor
 * @param message   Message to send
 * @return
 */
static int sendMessageToSocket(int socketFd, char* message);

/**
 * Read a received message from the socket
 * @method readMessageFromSocket
 * @param socketFd  Socket File descriptor
 * @return message  Received message
 */
static char* readMessageFromSocket(int socketFd);


#endif //CONTROLLER_NETWORKSERVICE_H
