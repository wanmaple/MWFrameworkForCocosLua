/******************************
 Description: JSON parser.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONPARSER__
#define __JSON_JSONPARSER__

#include "../base/mwbase.h"
#include "libjson/libjson.h"

MW_FRAMEWORK_BEGIN

class MWJsonObject;
class MWJsonArray;

class MW_DLL MWJsonParser
{
    /**
     * JsonParser is a singleton.
     */
    MW_SINGLETON(MWJsonParser);
public:
    /**
     * Parse the json string to json structures(JsonObject/JsonArray).
     *
     * @param jsonStr Json string.
     *
     * @return Return json object if it's a valid string, or return nullptr.
     */
    cocos2d::Ref *parseString(const std::string &jsonStr);
    
    /**
     * Parse the json file to json structures(JsonObject/JsonArray).
     *
     * @param jsonPath Json file path.
     *
     * @return Return json object if it's a valid string, or return nullptr.
     */
    cocos2d::Ref *parseFile(const std::string &jsonPath);
    
private:
    cocos2d::Ref *parseJsonNode(JSONNODE *jsonNode);
    
    MWJsonObject *parseToJsonObject(JSONNODE *jsonNode);
    
    MWJsonArray *parseToJsonArray(JSONNODE *jsonNode);
};

MW_FRAMEWORK_END

#endif /* defined(__JSON_JSONPARSER__) */
