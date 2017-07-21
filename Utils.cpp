//
// Created by narvena on 21/07/17.
//

#include "Utils.h"

Json::Value Utils::parseJsonString(std::string jsonString)
{
    //std::string strJson = "{\"mykey\" : \"myvalue\"}"; // need escape the quotes

    Json::Value jsonObject;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( jsonString.c_str(), jsonObject );     //parse process
    if ( !parsingSuccessful )
    {
        std::cout  << "Failed to parse"
                   << reader.getFormattedErrorMessages();
        return 0;
    }
    //std::cout << jsonObject.get("mykey", "A Default Value if not exists" ).asString() << std::endl;

    return jsonObject;
}