//
// Created by narvena on 22/06/17.
//

#include "MQTTService.h"

//volatile MQTTClient_deliveryToken deliveredToken;

MQTTService::MQTTService() {}
MQTTService::~MQTTService(){

    if(m_callback)
        delete m_callback;

}

void MQTTService::startMQTTServiceThread()
{
    openColorSocketServer(COLOR_SOCKET_PORT, COLOR_SOCKET_ADR);

    initMQTTClient();
}

void MQTTService::openColorSocketServer(unsigned int pPort, const char* pIp)
{
    colorSocketFileDescriptor = NetworkService::openSocket(pPort, pIp);
}
void MQTTService::openButtonSocketServer(unsigned int pPort, const char* pIp)
{
    buttonSocketFileDescriptor = NetworkService::openSocket(pPort, pIp);
}

void MQTTService::initMQTTClient()
{
    std::cout << "MQTTService::initMQTTClient ---- BEGINNING OF FUNCTION " << std::endl;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    async_client_ptr = std::make_shared<mqtt::async_client>(BROKER_ADDRESS, MQTT_CLIENT_ID);

    m_callback  = new callback(*async_client_ptr, connOpts);
    async_client_ptr->set_callback(*m_callback);

    // MQTT connection
    while(!isMQTTClientConnected)
    {
        connectClient();
        //todo add delay 1-2sec
    }

    m_callback->setColorSocketFd(&colorSocketFileDescriptor);

    subscribeToTopic(TOPIC, QOS);

    /*char * msg = "toto !!!!!!";
    char* messageToSend = "{\"type\" : \"1\", \"data\" : \"0,2,3,4\"}\n";

    while(isMQTTClientConnected){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        sendMessageToTopic(TOPIC, messageToSend, QOS);
    }*/

}
void MQTTService::connectClient() {
    try {
        std::cout << "MQTTService::connectClient ---- Connecting to the MQTT server...  " << std::endl << std::flush;
        connection_token = async_client_ptr->connect(connOpts);
        connection_token->wait();
        std::cout << "MQTTService::connectClient ---- Connected to MQTT server !  " << std::endl;
        isMQTTClientConnected = true;
    }
    catch (const mqtt::exception&) {
        std::cerr << "\nMQTTService::connectClient ---- ERROR: Unable to connect to MQTT server: '"
                  << BROKER_ADDRESS << "'" << std::endl;
        //return 1;
    }
}

void MQTTService::disconnectClient() {

    try {
        std::cout << "\nMQTTService::disconnectClient ---- Disconnecting from the MQTT server... " << std::endl << std::flush;
        async_client_ptr->disconnect()->wait();
        std::cout << "MQTTService::disconnectClient ---- OK" << std::endl;
        isMQTTClientConnected = false;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        //return 1;
    }
}


void MQTTService::subscribeToTopic(const std::string pTopic, const int pQos)
{
    try {
        mqtt::token_ptr subscribeToken;
        std::cout << "MQTTService::subscribeToTopic ---- Topic name :" << pTopic << std::endl;
        subscribeToken = async_client_ptr->subscribe(pTopic, pQos);
        subscribeToken->wait();
        std::cout << "MQTTService::subscribeToTopic ---- Subscribed ! " << std::endl;
    }
    catch (const mqtt::exception&) {
        std::cerr << "\nMQTTService::subscribeToTopic ---- ERROR: Unable to subscribe to topic: '"
                  << pTopic << "'" << std::endl;
        //return 1;
    }
}

void MQTTService::sendMessageToTopic(const std::string pTopic, char* pMessage, const int pQos) {
    std::cout << "\nMQTTService::sendMessageToTopic ---- Sending message..." << pMessage
              << " on topic :" << pTopic << std::endl;
    mqtt::message_ptr pubmsg = mqtt::make_message(pTopic, pMessage);
    pubmsg->set_qos(pQos);
    async_client_ptr->publish(pubmsg);//->wait_for(TIMEOUT);
    std::cout << "MQTTService::sendMessageToTopic ---- Message sent" << std::endl;

}
