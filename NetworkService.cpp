//
// Created by narvena on 09/07/17.
//

#include "NetworkService.h"

void NetworkService::error(const char *msg) {
    perror(msg);
    exit(0);
}

int NetworkService::connectToSocket(unsigned int port, const char *ip) {
    int socketFd;
    bool isConnectionEstablished = false;
    struct sockaddr_in serverAddress;
    struct hostent *server;
    char buffer[256];

    socketFd = socket(AF_INET, SOCK_STREAM, 0);   //creates the socket, type AF_INET and in TCP.
    // 0 = uses default protocol for current address family
    // returns the sockets file descriptor.
    server = gethostbyname(ip);


    std::cout << "NetworkService::connectToSocket ---- socketFd : " << socketFd << std::endl;
    std::cout << "NetworkService::connectToSocket ---- IP requested : " << ip << std::endl;
    std::cout << "NetworkService::connectToSocket ---- server address : " << server->h_addr << std::endl;


    memset((char *) &serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *) server->h_addr,//h_addr -> contains server IP address. Here, we copy the IP address to serverAddress struct
          (char *) &serverAddress.sin_addr.s_addr,
          server->h_length);
    serverAddress.sin_port = htons(port);


    std::cout << "NetworkService::connectToSocket ---- IP address : " << serverAddress.sin_addr.s_addr << std::endl;
    std::cout << "NetworkService::connectToSocket ---- Port : " << serverAddress.sin_port << std::endl;

    // Try to connect to socket until connection is established
    while (!isConnectionEstablished) {
        //std::cout << "NetworkService::connectToSocket ---- Attempting to connect to socket " << ip << ":" << port << "..." << std::endl;

        // try to connect to the server
        if (connect(socketFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
            //perror("NetworkService::connectToSocket ---- ERROR connecting");
        } else {
            isConnectionEstablished = true;
            std::cout << "NetworkService::connectToSocket ---- Connected to " << ip << ":" << port << std::endl;
            return socketFd;
        }
    }
}

int NetworkService::closeConnectionToSocket(int socketFileDescriptor) {
    return closeSocket(socketFileDescriptor);
}

int NetworkService::openSocket(unsigned int port, const char *ip) { //todo rename it to openSocketServer
    std::cout << "NetworkService::openSocket -- opening socket" << ip << ":" << port << std::endl;

    int socketFd,
            clientSocketFd,
            n;

    bool isClientConnected = false;
    socklen_t cliLength;                            // client length
    char buffer[256];                               //reception buffer

    sockaddr_in serverAddress,
            clientAddress;


    socketFd = socket(AF_INET, SOCK_STREAM, 0);     // Create socket

    memset((char *) &serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;             //AF_INET -> to use inter-network connection (UDp, TCP)
    serverAddress.sin_port = htons(port);           //htons -> this writes the port number in network byte order
    serverAddress.sin_addr.s_addr = inet_addr(ip);  //IP address

    std::cout << "NetworkService::openSocket ---- IP address : " << serverAddress.sin_addr.s_addr << std::endl;
    std::cout << "NetworkService::openSocket ---- Port : " << serverAddress.sin_port << std::endl;

    // binds the socket to its port
    if (bind(socketFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        error("NetworkService::openSocket ---- ERROR on binding");
    else
        std::cout << "NetworkService::openSocket ---- socket binding SUCCESS  " << socketFd << std::endl;

    int enable = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        error("NetworkService::openSocket ---- setsockopt(SO_REUSEADDR) failed");

    listen(socketFd, 5);                            //5 = waiting list of clients to be accepted

    while (!isClientConnected) {
        std::cout << "NetworkService::openSocket ---- Waiting for client connection..." << std::endl;
        cliLength = sizeof(clientAddress);
        // Accept first connection
        clientSocketFd = accept(socketFd,
                                (struct sockaddr *) &clientAddress,
                                &cliLength);    // allocation of client address memory needed

        if (clientSocketFd < 0)
            error("NetworkService::openSocket ---- ERROR while accepting client connection");
        else
            isClientConnected = true;

        std::cout << "NetworkService::openSocket ---- clientSocketFd = " << clientSocketFd << std::endl;
    }
    return clientSocketFd;
}

int NetworkService::closeSocket(int socketFileDescriptor) {
    int returnCode;
    returnCode = close(socketFileDescriptor);

    if (returnCode < 0)
        error("NetworkService::closeSocket ---- ERROR closing connection to socket");

    return returnCode;
}

int NetworkService::sendMessageToSocket(int socketFd, char *message) {
    //this is to put in an infinite loop server-side -> writes a message when asked (?)
    int returnCode;
    char buffer[256];
    memset(buffer, 0, 256);
    strcpy(buffer, message);
    returnCode = write(socketFd, buffer, strlen(buffer));
    if (returnCode < 0)
        error("NetworkService::sendMessageToSocket ---- ERROR writing to socket");
    return returnCode;
}

int NetworkService::readMessageFromSocket(int socketFd, char *buffer, const int length) {
    int returnCode;
    //char buffer[256];
    //memset(buffer, 0, 256);
    returnCode = read(socketFd, buffer, length);
    if (returnCode < 0)
        error("NetworkService::readMessageFromSocket ---- ERROR reading from socket");
    return returnCode;
}

NetworkService::NetworkService() {};

NetworkService::~NetworkService() {};
