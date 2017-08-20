//
// Created by narvena on 21/07/17.
//

#include "Utils.h"

bool Utils::parseJsonString(std::string jsonString, Json::Value * jsonObject)
{
    //std::string strJson = "{\"mykey\" : \"myvalue\"}"; // need escape the quotes

    //Json::Value jsonObject;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( jsonString.c_str(), *jsonObject );     //parse process
    if ( !parsingSuccessful )
    {
        std::cout  << "Utils::parseJsonString ---- Failed to parse"
                   << reader.getFormattedErrorMessages()
                   << std::endl;
    }
    std::cout  << "Utils::parseJsonString ---- Success parsing"
               << jsonObject->get("type", "MELKFJSMEL").asString()
               << std::endl;
    return parsingSuccessful;
    //std::cout << jsonObject.get("mykey", "A Default Value if not exists" ).asString() << std::endl;
}