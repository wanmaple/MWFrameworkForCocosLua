#include "MWJsonParser.h"
#include "MWJsonStructure.h"
#include "cocos2d.h"

using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWJsonParser::MWJsonParser()
{
}

Ref *MWJsonParser::parseString(const std::string &jsonStr)
{
    JSONNODE *lpNode = json_parse(jsonStr.c_str());
    
    Ref *pObj = this->parseJsonNode(lpNode);
    json_delete(lpNode);
    
    return pObj;
}

Ref *MWJsonParser::parseFile(const std::string &jsonPath)
{
    std::string buffer;
    Data data = FileUtils::getInstance()->getDataFromFile(jsonPath.c_str());
    unsigned char *lpFileData = data.getBytes();
    unsigned long fileSize = data.getSize();
    if (lpFileData) {
        for (unsigned long i = 0; i < fileSize; ++i) {
            buffer.push_back(lpFileData[i]);
        }
        delete [] lpFileData;
    }
    return this->parseString(buffer);
}

Ref *MWJsonParser::parseJsonNode(JSONNODE *jsonNode)
{
    if (json_type(jsonNode) == JSON_NODE) {
        return this->parseToJsonObject(jsonNode);
    } else if (json_type(jsonNode) == JSON_ARRAY) {
        return this->parseToJsonArray(jsonNode);
    }
    return nullptr;
}

MWJsonObject *MWJsonParser::parseToJsonObject(JSONNODE *jsonNode)
{
    MWJsonObject *pJson = MWJsonObject::create();
    JSONNODE_ITERATOR iter = json_begin(jsonNode);
    while (iter != json_end(jsonNode)) {
        if (*iter == nullptr) {
            CCLOG("Invalid json.");
            return nullptr;
        }
        char nodeType = json_type(*iter);
        json_char *szNodeName = json_name(*iter);
        switch (nodeType) {
            case JSON_NULL:
                // maybe need some other solution. todo
                pJson->putString(szNodeName, "");
                break;
            case JSON_BOOL:
                pJson->putBoolean(szNodeName, json_as_bool(*iter));
                break;
            case JSON_NUMBER:
                pJson->putNumber(szNodeName, json_as_float(*iter));
                break;
            case JSON_STRING:
            {
                json_char *szNodeValue = json_as_string(*iter);
                pJson->putString(szNodeName, szNodeValue);
                json_free(szNodeValue);
            }
                break;
            case JSON_NODE:
                pJson->putJsonObject(szNodeName, this->parseToJsonObject(*iter));
                break;
            case JSON_ARRAY:
                pJson->putJsonArray(szNodeName, this->parseToJsonArray(*iter));
                break;
            default:
                break;
        }
        json_free(szNodeName);
        ++iter;
    }
    
    return pJson;
}

MWJsonArray *MWJsonParser::parseToJsonArray(JSONNODE *jsonNode)
{
    MWJsonArray *pJson = MWJsonArray::create();
    JSONNODE_ITERATOR iter = json_begin(jsonNode);
    while (iter != json_end(jsonNode)) {
        if (*iter == nullptr) {
            CCLOG("Invalid json.");
            return nullptr;
        }
        char nodeType = json_type(*iter);
        switch (nodeType) {
            case JSON_NULL:
                // maybe need some other solution. todo
                pJson->appendString("");
                break;
            case JSON_BOOL:
                pJson->appendBoolean(json_as_bool(*iter));
                break;
            case JSON_NUMBER:
                pJson->appendNumber(json_as_float(*iter));
                break;
            case JSON_STRING:
            {
                json_char *szNodeValue = json_as_string(*iter);
                pJson->appendString(szNodeValue);
                json_free(szNodeValue);
            }
                break;
            case JSON_NODE:
                pJson->appendJsonObject(this->parseToJsonObject(*iter));
                break;
            case JSON_ARRAY:
                pJson->appendJsonArray(this->parseToJsonArray(*iter));
                break;
            default:
                break;
        }
        ++iter;
    }
    
    return pJson;
}

MW_FRAMEWORK_END