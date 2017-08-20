//
// Created by narvena on 25/07/17.
//

#include "MQTTCallback.h"

void callback::connected(const std::string& cause)
{
    std::cout << "\nMQTTCallback::connected ---- Connection success" << std::endl;

    //cli_.subscribe(TOPIC, QOS, nullptr, subListener_);    //this also causes Segmentation default
    cli_.subscribe(TOPIC, QOS);
}

// This demonstrates manually reconnecting to the broker by calling
// connect() again. This is a possibility for an application that keeps
// a copy of it's original connect_options, or if the app wants to
// reconnect with different options.
// Another way this can be done manually, if using the same options, is
// to just call the async_client::reconnect() method.
void callback::reconnect() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
        cli_.connect(connOpts_, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}

// Re-connection failure
void callback::on_failure(const mqtt::token& tok) {
    std::cout << "MQTTCallback::on_failure ---- Connection failed" << std::endl;
    if (++nretry_ > N_RETRY_ATTEMPTS)
        exit(1);
    reconnect();
}

// Re-connection success
void callback::on_success(const mqtt::token& tok) {
    std::cout << "\nMQTTCallback::on_success ---- Connection success" << std::endl;
    std::cout << "\nMQTTCallback::on_success ---- Subscribing to topic '" << TOPIC << "'\n"
              << "\tfor client " << MQTT_CLIENT_ID
              << " using QoS" << QOS << "\n"
              << "\nPress Q<Enter> to quit\n" << std::endl;

    cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void callback::connection_lost(const std::string& cause) {
    std::cout << "\nMQTTCallback::connection_lost ---- Connection lost" << std::endl;
    if (!cause.empty())
        std::cout << "\tcause: " << cause << std::endl;

    std::cout << "MQTTCallback::connection_lost ---- Reconnecting..." << std::endl;
    nretry_ = 0;
    reconnect();
}

// Callback for when a message arrives.
void callback::message_arrived(mqtt::const_message_ptr msg) {
    Json::Value jsonMsg;
    std::string msgType;
    bool isMsgConversionOk;
    std::string msgContent;
    const char * convertedMsgContent;

    int returnCode;
    std::cout << "MQTTCallback::message_arrived ---- Message arrived" << std::endl;
    std::cout << "\tMQTTCallback::message_arrived ---- topic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tMQTTCallback::message_arrived ---- payload: '" << msg->to_string() << "'\n" << std::endl;

    if(colorSocketFd != NULL)
    {
        isMsgConversionOk = Utils::parseJsonString(msg->to_string(), &jsonMsg);

        if(isMsgConversionOk)
        {
            msgType = jsonMsg.get("type", "This key doesn't exist!").asString();
            std::cout << "MQTTCallback::message_arrived ---- Message type =" << msgType << std::endl;
            if(msgType.compare("1") == 0)
            {
                std::cout << "MQTTCallback::message_arrived ---- It's to change colors!" << std::endl;

                msgContent = jsonMsg.get("data", "No data in message...").asString();
                msgContent += '\n';
                convertedMsgContent = msgContent.c_str();
                returnCode = NetworkService::sendMessageToSocket(*colorSocketFd, convertedMsgContent);

                std::cout << "MQTTCallback::message_arrived ---- sendMessageToSocket returnCode"
                          << returnCode
                          << std::endl;
            }
        }

    }
}

void callback::delivery_complete(mqtt::delivery_token_ptr token) {
    std::cout << "MQTTCallback:: Message delivered " << std::endl;
}

callback::callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
        : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
callback::~callback() {}

void callback::setColorSocketFd(int *socketFd)
{
    std::cout << "MQTTCallback::setColorSocketFd ---- given socketFd: "
              << socketFd << std::endl;
    colorSocketFd = socketFd;
}

void callback::setButtonSocketFd(int *socketFd)
{
    buttonSocketFd = socketFd;
}
