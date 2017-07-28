//
// Created by narvena on 26/07/17.
//

#ifndef CONTROLLER_MQTTACTIONLISTENER_H
#define CONTROLLER_MQTTACTIONLISTENER_H


class action_listener : public virtual mqtt::iaction_listener
{
    std::string name_;

    void on_failure(const mqtt::token& tok);

    void on_success(const mqtt::token& tok);

public:
    action_listener(const std::string& name);
};

#endif //CONTROLLER_MQTTACTIONLISTENER_H
