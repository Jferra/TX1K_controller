//
// Created by narvena on 21/07/17.
//

#ifndef CONTROLLER_UTILS_H
#define CONTROLLER_UTILS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "json/json.h"

class Utils{
public:
    /**
     * Creates a Json Object from a given Json string
     * @method parseJsonString
     * @param std::string jsonString
     * @return Json::Value jsonObject
     */
    static Json::Value parseJsonString(std::string jsonString);

private:
    Utils() {};
};


#endif //CONTROLLER_UTILS_H
