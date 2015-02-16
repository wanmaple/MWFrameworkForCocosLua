#include "MWJsonFormatter.h"
#include "MWJsonElement.h"
#include "MWJsonStructure.h"

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWJsonFormatter::MWJsonFormatter()
{
}

string MWJsonFormatter::format(Ref *json, bool isPretty)
{
    JSONNODE *jsonNode = this->formatToJsonNode(json);
    json_char *jsonChar = isPretty ? json_write_formatted(jsonNode) : json_write(jsonNode);
    string jsonStr(jsonChar);
    json_free(jsonChar);
    json_delete(jsonNode);
    
    return jsonStr;
}

JSONNODE *MWJsonFormatter::formatToJsonNode(Ref *json)
{
    CCASSERT(json, "Invalid json.");
    MWJsonObject *pJsonObj = nullptr;
    MWJsonArray *pJsonAry = nullptr;
    if ((pJsonObj = dynamic_cast<MWJsonObject*>(json)) != nullptr) {
        return this->formatJsonObjectToJsonNode(pJsonObj);
    } else if ((pJsonAry = dynamic_cast<MWJsonArray*>(json)) != nullptr) {
        return this->formatJsonArrayToJsonNode(pJsonAry);
    }
    CCASSERT(false, "Invalid json type.");
    return nullptr;
}

JSONNODE *MWJsonFormatter::formatJsonObjectToJsonNode(MWJsonObject *json)
{
    CCASSERT(json, "Invalid JsonObject.");
    JSONNODE *jsonNode = json_new(JSON_NODE);
    int count = json->count();
    auto keys = json->allKeys();
    for (int i = 0; i < count; ++i) {
        string szKey = keys[i];
        Ref *val = json->_dataHolder->objectForKey(szKey);
        MWJsonBoolean *pJsonBool = nullptr;
        MWJsonNumber *pJsonNum = nullptr;
        MWJsonString *pJsonStr = nullptr;
        MWJsonObject *pJsonObj = nullptr;
        MWJsonArray *pJsonAry = nullptr;
        if ((pJsonBool = dynamic_cast<MWJsonBoolean*>(val)) != nullptr) {
            json_push_back(jsonNode, json_new_b(szKey.c_str(), pJsonBool->boolValue()));
        } else if ((pJsonNum = dynamic_cast<MWJsonNumber*>(val)) != nullptr) {
            json_push_back(jsonNode, json_new_f(szKey.c_str(), pJsonNum->numberValue()));
        } else if ((pJsonStr = dynamic_cast<MWJsonString*>(val)) != nullptr) {
            json_push_back(jsonNode, json_new_a(szKey.c_str(), pJsonStr->stringValue()));
        } else if ((pJsonObj = dynamic_cast<MWJsonObject*>(val)) != nullptr) {
            JSONNODE *node = this->formatJsonObjectToJsonNode(pJsonObj);
            json_set_name(node, szKey.c_str());
            json_push_back(jsonNode, node);
        } else if ((pJsonAry = dynamic_cast<MWJsonArray*>(val)) != nullptr) {
            JSONNODE *node = this->formatJsonArrayToJsonNode(pJsonAry);
            json_set_name(node, szKey.c_str());
            json_push_back(jsonNode, node);
        }
    }
    
    return jsonNode;
}

JSONNODE *MWJsonFormatter::formatJsonArrayToJsonNode(MWJsonArray *json)
{
    CCASSERT(json, "Invalid JsonObject.");
    JSONNODE *jsonNode = json_new(JSON_ARRAY);
    int count = json->count();
    for (int i = 0; i < count; ++i) {
        Ref *val = json->_dataHolder->objectAtIndex(i);
        MWJsonBoolean *pJsonBool = nullptr;
        MWJsonNumber *pJsonNum = nullptr;
        MWJsonString *pJsonStr = nullptr;
        MWJsonObject *pJsonObj = nullptr;
        MWJsonArray *pJsonAry = nullptr;
        if ((pJsonBool = dynamic_cast<MWJsonBoolean*>(val)) != nullptr) {
            json_push_back(jsonNode, json_new_b(nullptr, pJsonBool->boolValue()));
        } else if ((pJsonNum = dynamic_cast<MWJsonNumber*>(val)) != nullptr) {
            json_push_back(jsonNode, json_new_f(nullptr, pJsonNum->numberValue()));
        } else if ((pJsonStr = dynamic_cast<MWJsonString*>(val)) != nullptr) {
            json_push_back(jsonNode, json_new_a(nullptr, pJsonStr->stringValue()));
        } else if ((pJsonObj = dynamic_cast<MWJsonObject*>(val)) != nullptr) {
            json_push_back(jsonNode, this->formatJsonObjectToJsonNode(pJsonObj));
        } else if ((pJsonAry = dynamic_cast<MWJsonArray*>(val)) != nullptr) {
            json_push_back(jsonNode, this->formatJsonArrayToJsonNode(pJsonAry));
        }
    }
    
    return jsonNode;
}

MW_FRAMEWORK_END