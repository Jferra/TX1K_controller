//
// Created by narvena on 26/07/17.
//

#include "MQTTActionListener.h"

void MQTTActionListener::on_failure(const mqtt::token& tok) override {
    std::cout << name_ << " failure";
    if (tok.get_message_id() != 0)
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    std::cout << std::endl;
}

void MQTTActionListener::on_success(const mqtt::token& tok) override {
    std::cout << name_ << " success";
    if (tok.get_message_id() != 0)
        std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    auto top = tok.get_topics();
    if (top && !top->empty())
        std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
    std::cout << std::endl;
}

MQTTActionListener::action_listener(const std::string& name) : name_(name) {}