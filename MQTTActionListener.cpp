//
// Created by narvena on 26/07/17.
//

#include "MQTTActionListener.h"

void action_listener::on_failure(const mqtt::token& tok) {
    std::cout << "MQTTActionListener::on_failure ---- " << name_ << " failure" << std::endl;
    if (tok.get_message_id() != 0)
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    std::cout << std::endl;
}

void action_listener::on_success(const mqtt::token& tok) {
    std::cout << "MQTTActionListener::on_success ---- " << name_ << " success" << std::endl;
    if (tok.get_message_id() != 0)
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    auto top = tok.get_topics();
    if (top && !top->empty())
        std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
    std::cout << std::endl;
}

action_listener::action_listener(const std::string& name) : name_(name) {}

action_listener::~action_listener() {}