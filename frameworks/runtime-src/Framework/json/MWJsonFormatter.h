/******************************
 Description: JSON formatter.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONFORMATTER__
#define __JSON_JSONFORMATTER__

#include "../base/mwbase.h"
#include "libjson/libjson.h"
#include <string>

MW_FRAMEWORK_BEGIN

class MWJsonObject;
class MWJsonArray;

class MW_DLL MWJsonFormatter
{
    /**
     * JsonFormatter is a singleton.
     */
    MW_SINGLETON(MWJsonFormatter);
public:
    /**
     * Format the json object(JsonObject/JsonArray) into string.
     *
     * @param json Json object.
     *
     * @return Return Formatted string.
     */
    std::string format(cocos2d::Ref *json, bool isPretty = false);
    
private:
    JSONNODE *formatToJsonNode(cocos2d::Ref *json);
    JSONNODE *formatJsonObjectToJsonNode(MWJsonObject *json);
    JSONNODE *formatJsonArrayToJsonNode(MWJsonArray *json);
};

MW_FRAMEWORK_END

#endif /* defined(__JSON_JSONFORMATTER__) */
