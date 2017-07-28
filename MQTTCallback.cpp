//
// Created by narvena on 25/07/17.
//

#include "MQTTCallback.h"

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
void callback::on_failure(const mqtt::token& tok) override {
    std::cout << "Connection failed" << std::endl;
    if (++nretry_ > N_RETRY_ATTEMPTS)
        exit(1);
    reconnect();
}

// Re-connection success
void callback::on_success(const mqtt::token& tok) override {
    std::cout << "\nConnection success" << std::endl;
    std::cout << "\nSubscribing to topic '" << TOPIC << "'\n"
              << "\tfor client " << CLIENT_ID
              << " using QoS" << QOS << "\n"
              << "\nPress Q<Enter> to quit\n" << std::endl;

    cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
}

// Callback for when the connection is lost.
// This will initiate the attempt to manually reconnect.
void callback::connection_lost(const std::string& cause) override {
    std::cout << "\nConnection lost" << std::endl;
    if (!cause.empty())
        std::cout << "\tcause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    nretry_ = 0;
    reconnect();
}

// Callback for when a message arrives.
void callback::message_arrived(mqtt::const_message_ptr msg) override {
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;

    //todo see async_subscribe
    if(colorSocketFd != -1)
    {
        // send message to socket
    }
}

void callback::delivery_complete(mqtt::delivery_token_ptr token) override {}

callback::callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
        : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}


void callback::setColorSocketFd(int socketFd)
{
    colorSocketFd = socketFd;
}

void callback::setButtonSocketFd(int socketFd)
{
    buttonSocketFd = socketFd;
}