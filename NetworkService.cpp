//
// Created by narvena on 09/07/17.
//

#include "NetworkService.h"

void NetworkService::error(const char *msg) {
    perror(msg);
    exit(0);
}

int NetworkService::connectToSocket(unsigned int port, char* ip){
    int socketFd;
    bool isConnectionEstablished = false;
    struct sockaddr_in serverAddress;
    struct hostent *server;
    char buffer[256];

    socketFd = socket(AF_INET, SOCK_STREAM, 0);   //creates the socket, type AF_INET and in TCP.
    // 0 = uses default protocol for current address family
    // returns the sockets file descriptor.
    server = gethostbyname(ip);

    memset((char *) &serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr,//h_addr -> contains server IP address. Here, we copy the IP address to serverAddress struct
          (char *)&serverAddress.sin_addr.s_addr,
          server->h_length);
    serverAddress.sin_port = htons(port);

    // Try to connect to socket until connection is established
    while(!isConnectionEstablished){
        std::cout << "Attempting to connect to socket " << port << ":" << ip << "...";
        if (connect(socketFd,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) {  // try to connect to the server
            perror("ERROR connecting");
        } else {
            isConnectionEstablished = true;
            return socketFd;
        }
    }
}

int NetworkService::closeConnectionToSocket(int socketFileDescriptor){
    return closeSocket(socketFileDescriptor);
}

int NetworkService::openSocket(unsigned int port, char* ip){
    int socketFd,
            newSocketFd,
            n;
    socklen_t cliLength;   // client length
    char buffer[256]; //reception buffer
    sockaddr_in serverAddress,
            clientAddress;


    socketFd = socket(AF_INET, SOCK_STREAM, 0);   // Create socket

    memset((char *) &serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET; //AF_INET -> to use inter-network connection (UDp, TCP)
    serverAddress.sin_port = htons(port); //htons -> this writes the port number in network byte order
    serverAddress.sin_addr.s_addr = inet_addr(ip);  //IP address

    if (bind(socketFd, (struct sockaddr *) &serverAddress,
             sizeof(serverAddress)) < 0)    // binds the socket to its port
        error("ERROR on binding");

    listen(socketFd,5); //5 = liste d'attente pour accepter connexion
    cliLength = sizeof(clientAddress);
    // Accept first connection
    newSocketFd = accept(socketFd,
                         (struct sockaddr *) &clientAddress,
                         &cliLength);    // allocation of client address memory needed
    if(newSocketFd < 0)
        error("ERROR while accepting client connection");

    return newSocketFd;
}

int NetworkService::closeSocket(int socketFileDescriptor){
    int returnCode;
    returnCode = close(socketFileDescriptor);

    if(returnCode < 0)
        error("ERROR closing connection to socket");

    return returnCode;
}

int NetworkService::sendMessageToSocket(int socketFd, char* message){
    //this is to put in an infinite loop server-side -> writes a message when asked (?)
    int returnCode;
    char buffer[256];
    memset(buffer, 0, 256);
    strcpy(buffer, message);
    returnCode = write(socketFd,buffer,strlen(buffer));
    if (returnCode < 0)
        error("ERROR writing to socket");
    return returnCode;
}

char* NetworkService::readMessageFromSocket(int socketFd){
    int returnCode;
    char buffer[256];
    memset(buffer, 0, 256);
    returnCode = read(socketFd,buffer,255);
    if (returnCode < 0)
        error("ERROR reading from socket");
    else
        return buffer;
}
