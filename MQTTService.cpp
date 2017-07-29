//
// Created by narvena on 22/06/17.
//

#include "MQTTService.h"

//volatile MQTTClient_deliveryToken deliveredToken;

MQTTService::MQTTService(){}
MQTTService::~MQTTService(){}

void MQTTService::startMQTTServiceThread()
{
    initMQTTClient();

    openColorSocketServer(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);

    // MQTT connection
    while(!isClientConnected)
    {
        connectClient();
    }

    char* messageToSend = "{\"type\" : \"1\", \"data\" : \"KALIMBA\"}\n";

    sendMessageToTopic(TOPIC, messageToSend, QOS);
}

void MQTTService::openColorSocketServer(unsigned int pPort, char* pIp)
{
    colorSocketFileDescriptor = NetworkService::openSocket(pPort, pIp);
}
void MQTTService::openButtonSocketServer(unsigned int pPort, char* pIp)
{
    buttonSocketFileDescriptor = NetworkService::openSocket(pPort, pIp);
}

void MQTTService::initMQTTClient()
{
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    mqtt::async_client client(BROKER_ADDRESS, MQTT_CLIENT_ID);

    callback cb(client, connOpts);
    client.set_callback(cb);

    cb.setColorSocketFd(colorSocketFileDescriptor);

    /*
    conn_opts = MQTTClient_connectOptions_initializer;
    pubmsg = MQTTClient_message_initializer;
    clientID = pClientID;

    MQTTClient_create(&client,
                      brokerAddress,
                      clientID,
                      MQTTCLIENT_PERSISTENCE_NONE,
                      NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // Set MQTTClient callbacks
    MQTTClient_setCallbacks(client, NULL, connectionLost, messageArrivedCallback, delivered);*/
}
/*void MQTTService::initMQTTClient(char* brokerAddress) {
    MQTTClient_create(&client, brokerAddress, clientID,
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
}*/

void MQTTService::connectClient() {
    try {
        std::cout << "Connecting to the MQTT server..." << std::flush;
        client.connect(connOpts, nullptr, cb);
        isClientConnected = true;
    }
    catch (const mqtt::exception&) {
        std::cerr << "\nERROR: Unable to connect to MQTT server: '"
                  << BROKER_ADDRESS << "'" << std::endl;
        //return 1;
    }

    /*int isClientConnected = false;

    while(!isClientConnected)
    {
        if ((retCode = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
        {
            printf("Failed to connect, return code %d\n", retCode);
        }
        else
        {
            isClientConnected = true;
        }
    }*/
}

void MQTTService::disconnectClient() {

    try {
        std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
        client.disconnect()->wait();
        std::cout << "OK" << std::endl;
        isClientConnected = false;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        //return 1;
    }

    /*MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);*/
}

/*
void MQTTService::subscribeToTopic(char* pTopic, int pQos)
{
    std::cout << "MQTTService::subscribeToTopic " << pTopic << std::endl;
    MQTTClient_subscribe(client, pTopic, pQos);
}*/

void MQTTService::sendMessageToTopic(const std::string pTopic, char* pMessage, const int pQos) {
    std::cout << "\nSending message..." << std::endl;
    mqtt::message_ptr pubmsg = mqtt::make_message(pTopic, pMessage);
    pubmsg->set_qos(pQos);
    client.publish(pubmsg)->wait_for(TIMEOUT);
    std::cout << "  ...OK" << std::endl;

    /*pubmsg.payload = pMessage;
    pubmsg.payloadlen = strlen(pMessage);
    pubmsg.qos = pQos;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, pTopic, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
                   "on topic %s for client with ClientID: %s\n",
           (int)(TIMEOUT/1000), pMessage, pTopic, clientID);
    retCode = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);*/
}
/*
void MQTTService::unsubscribeFromTopic(char* pTopic){
    MQTTClient_unsubscribe(clientID, pTopic);
}


void MQTTService::delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredToken = dt;
}

int MQTTService::messageArrivedCallback(void *context, char* topicName, int topicLen, MQTTClient_message *message)
{
    void* payloadptr;
    int hasMessageArrived;
    char* messageContent;
    Json::Value jsonMessage;
    payloadptr = message->payload;
    messageContent = (char*)payloadptr;

    std::cout << "Message received on topic " << topicName << " :  " << messageContent << std::endl;

    std::string str(messageContent);
    jsonMessage = Utils::parseJsonString(str);

    std::cout << jsonMessage.get("mykey", "A Default Value if not exists" ).asString() << std::endl;

    /*switch(std::stoi(jsonMessage.get("type", "null").asString()))
    {
        case BUTTON_PRESSED:
            hasMessageArrived = NetworkService::sendMessageToSocket(colorSocketFileDescriptor, jsonMessage.get("data", "null").asString());
            break;
        case SET_COLORS:
            hasMessageArrived = NetworkService::sendMessageToSocket(buttonSocketFileDescriptor, jsonMessage.get("data", "null").asString());
            break;

    }*/

    // Free memory allocated to the message once it is processed
    /*MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return hasMessageArrived;
}

void MQTTService::connectionLost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}*/
