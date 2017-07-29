//
// Created by narvena on 26/07/17.
//


#ifndef CONTROLLER_MQTTACTIONLISTENER_H
#define CONTROLLER_MQTTACTIONLISTENER_H

#include <stdio.h>
#include <stdlib.h>
#include "mqtt/async_client.h"

class action_listener : public virtual mqtt::iaction_listener
{
    std::string name_;

    void on_failure(const mqtt::token& tok) override;

    void on_success(const mqtt::token& tok) override;

public:
    action_listener(const std::string& name);
    virtual ~action_listener();
};

#endif //CONTROLLER_MQTTACTIONLISTENER_H
