//
// Created by narvena on 25/07/17.
//

#ifndef CONTROLLER_MQTTCALLBACK_H
#define CONTROLLER_MQTTCALLBACK_H

#include "MQTTActionListener.h"

const std::string MQTT_CLIENT_ID("Toto");
const std::string TOPIC("totopic");
const int	QOS = 0;
const int	N_RETRY_ATTEMPTS = 5;

const auto TIMEOUT = std::chrono::seconds(10);

class callback : public virtual mqtt::callback,
                 public virtual mqtt::iaction_listener
{
    // Counter for the number of connection retries
    int nretry_;
    // The MQTT client
    mqtt::async_client& cli_;
    // Options to use if we need to reconnect
    mqtt::connect_options& connOpts_;
    // An action listener to display the result of actions.
    action_listener subListener_;
    // Color socket File descriptor
    int colorSocketFd = -1;
    // Button socket File descriptor
    int buttonSocketFd = -1;

    // Callback on connection success
    void connected(const std::string& cause) override;

    // This demonstrates manually reconnecting to the broker by calling
    // connect() again. This is a possibility for an application that keeps
    // a copy of it's original connect_options, or if the app wants to
    // reconnect with different options.
    // Another way this can be done manually, if using the same options, is
    // to just call the async_client::reconnect() method.
    void reconnect();

    // Re-connection failure
    void on_failure(const mqtt::token& tok) override;

    // Re-connection success
    void on_success(const mqtt::token& tok) override;

    // Callback for when the connection is lost.
    // This will initiate the attempt to manually reconnect.
    void connection_lost(const std::string& cause) override;

    // Callback for when a message arrives.
    void message_arrived(mqtt::const_message_ptr msg) override;

    void delivery_complete(mqtt::delivery_token_ptr token) override;

public:
    callback(mqtt::async_client& cli, mqtt::connect_options& connOpts);
    virtual ~callback();

    void setColorSocketFd(int socketFd);

    void setButtonSocketFd(int socketFd);
};

#endif //CONTROLLER_MQTTCALLBACK_H
