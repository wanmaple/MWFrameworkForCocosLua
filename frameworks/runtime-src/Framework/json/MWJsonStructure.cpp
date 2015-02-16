#include "MWJsonStructure.h"
#include "MWJsonElement.h"
#include "MWJsonParser.h"
#include "MWJsonFormatter.h"

MW_FRAMEWORK_BEGIN

/** JsonObject implementation **/
MWJsonObject::MWJsonObject()
: _dataHolder(new MWDictionary())
{
}

MWJsonObject::~MWJsonObject()
{
    CC_SAFE_RELEASE(_dataHolder);
}

bool MWJsonObject::init()
{
    return true;
}

MWJsonObject *MWJsonObject::createWithString(const std::string &jsonStr)
{
    return dynamic_cast<MWJsonObject*>(MWJsonParser::getInstance()->parseString(jsonStr));
}

MWJsonObject *MWJsonObject::createWithFile(const std::string &jsonPath)
{
    return dynamic_cast<MWJsonObject*>(MWJsonParser::getInstance()->parseFile(jsonPath));
}

bool MWJsonObject::hasKey(const std::string &key)
{
    return _dataHolder->objectForKey(key) != nullptr;
}

MW_UINT MWJsonObject::count()
{
    return _dataHolder->count();
}

void MWJsonObject::putBoolean(const std::string &key, bool value)
{
    auto val = MWJsonBoolean::create(value);
    _dataHolder->setObjectForKey(key, val);
}

bool MWJsonObject::getBoolean(const std::string &key) const
{
    auto val = _dataHolder->objectForKey(key);
    CCASSERT(val, "Invalid key.");
    IJsonElement *pVal = dynamic_cast<IJsonElement*>(val);
    return pVal->boolValue();
}

void MWJsonObject::putNumber(const std::string &key, double value)
{
    auto val = MWJsonNumber::create(value);
    _dataHolder->setObjectForKey(key, val);
}

double MWJsonObject::getNumber(const std::string &key) const
{
    auto val = _dataHolder->objectForKey(key);
    CCASSERT(val, "Invalid key.");
    IJsonElement *pVal = dynamic_cast<IJsonElement*>(val);
    return pVal->numberValue();
}

void MWJsonObject::putString(const std::string &key, const std::string &value)
{
    auto val = MWJsonString::create(value);
    _dataHolder->setObjectForKey(key, val);
}

const char *MWJsonObject::getString(const std::string &key) const
{
    auto val = _dataHolder->objectForKey(key);
    CCASSERT(val, "Invalid key.");
    IJsonElement *pVal = dynamic_cast<IJsonElement*>(val);
    return pVal->stringValue();
}

void MWJsonObject::putJsonObject(const std::string &key, MWJsonObject *value)
{
    _dataHolder->setObjectForKey(key, value);
}

MWJsonObject *MWJsonObject::getJsonObject(const std::string &key) const
{
    return dynamic_cast<MWJsonObject*>(_dataHolder->objectForKey(key));
}

void MWJsonObject::putJsonArray(const std::string &key, MWJsonArray *value)
{
    _dataHolder->setObjectForKey(key, value);
}

MWJsonArray *MWJsonObject::getJsonArray(const std::string &key) const
{
    return dynamic_cast<MWJsonArray*>(_dataHolder->objectForKey(key));
}

void MWJsonObject::remove(const std::string &key)
{
    _dataHolder->removeObjectForKey(key);
}

void MWJsonObject::clear()
{
    _dataHolder->clear();
}

std::vector<const std::string> MWJsonObject::allKeys()
{
    return _dataHolder->allKeys();
}

std::string MWJsonObject::toString()
{
    return MWJsonFormatter::getInstance()->format(this);
}

std::string MWJsonObject::toPrettyString()
{
    return MWJsonFormatter::getInstance()->format(this, true);
}

std::string MWJsonObject::toLuaString()
{
    // begining
    std::string luaStr = "{\n";
    auto keys = this->allKeys();
    int count = keys.size();
    for (MW_UINT i = 0; i < count; ++i) {
        // key
        const char *szKey = keys[i].c_str();
        luaStr.append("[\"");
        luaStr.append(szKey);
        luaStr.append("\"]");
        luaStr.append("=");
        // value
        Ref *pVal = _dataHolder->objectForKey(szKey);
        MWJsonBoolean *pJsonBool = nullptr;
        MWJsonNumber *pJsonNum = nullptr;
        MWJsonString *pJsonStr = nullptr;
        MWJsonObject *pJsonObj = nullptr;
        MWJsonArray *pJsonAry = nullptr;
        if ((pJsonBool = dynamic_cast<MWJsonBoolean*>(pVal)) != nullptr) {
            luaStr.append(pJsonBool->stringValue());
        } else if ((pJsonNum = dynamic_cast<MWJsonNumber*>(pVal)) != nullptr) {
            luaStr.append(pJsonNum->stringValue());
        } else if ((pJsonStr = dynamic_cast<MWJsonString*>(pVal)) != nullptr) {
            luaStr.append("[==[");
            luaStr.append(pJsonStr->stringValue());
            luaStr.append("]==]");
        } else if ((pJsonObj = dynamic_cast<MWJsonObject*>(pVal)) != nullptr) {
            std::string value = pJsonObj->toLuaString();
            luaStr.append(value);
        } else if ((pJsonAry = dynamic_cast<MWJsonArray*>(pVal)) != nullptr) {
            std::string value = pJsonAry->toLuaString();
            luaStr.append(value);
        }
        
        if (i < count - 1) {
            luaStr.append(",");
            luaStr.append("\n");
        }
    }
    // ending
    luaStr.append("\n}");
    return luaStr;
}

/** JsonArray implementation **/
MWJsonArray::MWJsonArray()
: _dataHolder(new MWArrayList())
{
}

MWJsonArray::~MWJsonArray()
{
    CC_SAFE_RELEASE(_dataHolder);
}

bool MWJsonArray::init()
{
    return true;
}

MWJsonArray *MWJsonArray::createWithString(const std::string &jsonStr)
{
    return dynamic_cast<MWJsonArray*>(MWJsonParser::getInstance()->parseString(jsonStr));
}

MWJsonArray *MWJsonArray::createWithFile(const std::string &jsonPath)
{
    return dynamic_cast<MWJsonArray*>(MWJsonParser::getInstance()->parseFile(jsonPath));
}

MW_UINT MWJsonArray::count()
{
    return _dataHolder->count();
}

void MWJsonArray::appendBoolean(bool value)
{
    auto val = MWJsonBoolean::create(value);
    _dataHolder->appendObject(val);
}

void MWJsonArray::insertBoolean(bool value, MW_UINT index)
{
    _dataHolder->setObjectAtIndex(MWJsonBoolean::create(value), index);
}

bool MWJsonArray::getBooleanAt(int index)
{
    auto val = (MWJsonBoolean*)_dataHolder->objectAtIndex(index);
    return val->boolValue();
}

void MWJsonArray::appendNumber(double value)
{
    auto val = MWJsonNumber::create(value);
    _dataHolder->appendObject(val);
}

void MWJsonArray::insertNumber(double value, MW_UINT index)
{
    _dataHolder->setObjectAtIndex(MWJsonNumber::create(value), index);
}

double MWJsonArray::getNumberAt(MW_UINT index)
{
    auto val = (MWJsonNumber*)_dataHolder->objectAtIndex(index);
    return val->numberValue();
}

void MWJsonArray::appendString(const std::string &value)
{
    auto val = MWJsonString::create(value);
    _dataHolder->appendObject(val);
}

void MWJsonArray::insertString(const std::string &value, int index)
{
    _dataHolder->setObjectAtIndex(MWJsonString::create(value), index);
}

const char *MWJsonArray::getStringAt(MW_UINT index)
{
    auto val = (MWJsonString*)_dataHolder->objectAtIndex(index);
    return val->stringValue();
}

void MWJsonArray::appendJsonObject(MWJsonObject *value)
{
    _dataHolder->appendObject(value);
}

void MWJsonArray::insertJsonObject(MWJsonObject *value, MW_UINT index)
{
    _dataHolder->setObjectAtIndex(value, index);
}

MWJsonObject *MWJsonArray::getJsonObjectAt(MW_UINT index)
{
    return dynamic_cast<MWJsonObject*>(_dataHolder->objectAtIndex(index));
}

void MWJsonArray::appendJsonArray(MWJsonArray *value)
{
    _dataHolder->appendObject(value);
}

void MWJsonArray::insertJsonArray(MWJsonArray *value, MW_UINT index)
{
    _dataHolder->setObjectAtIndex(value, index);
}

MWJsonArray *MWJsonArray::getJsonArrayAt(MW_UINT index)
{
    return dynamic_cast<MWJsonArray*>(_dataHolder->objectAtIndex(index));
}

void MWJsonArray::removeAt(MW_UINT index)
{
    _dataHolder->removeObjectAtIndex(index);
}

void MWJsonArray::clear()
{
    _dataHolder->clear();
}

std::string MWJsonArray::toString()
{
    return MWJsonFormatter::getInstance()->format(this);
}

std::string MWJsonArray::toPrettyString()
{
    return MWJsonFormatter::getInstance()->format(this, true);
}

std::string MWJsonArray::toLuaString()
{
    // begining
    std::string luaStr = "{\n";
    int num = this->count();
    for (int i = 0; i < num; ++i) {
        // value
        Ref *pVal = _dataHolder->objectAtIndex(i);
        MWJsonBoolean *pJsonBool = nullptr;
        MWJsonNumber *pJsonNum = nullptr;
        MWJsonString *pJsonStr = nullptr;
        MWJsonObject *pJsonObj = nullptr;
        MWJsonArray *pJsonAry = nullptr;
        if ((pJsonBool = dynamic_cast<MWJsonBoolean*>(pVal)) != nullptr) {
            luaStr.append(pJsonBool->stringValue());
        } else if ((pJsonNum = dynamic_cast<MWJsonNumber*>(pVal)) != nullptr) {
            luaStr.append(pJsonNum->stringValue());
        } else if ((pJsonStr = dynamic_cast<MWJsonString*>(pVal)) != nullptr) {
            luaStr.append("[==[");
            luaStr.append(pJsonStr->stringValue());
            luaStr.append("]==]");
        } else if ((pJsonObj = dynamic_cast<MWJsonObject*>(pVal)) != nullptr) {
            std::string value = pJsonObj->toLuaString();
            luaStr.append(value);
        } else if ((pJsonAry = dynamic_cast<MWJsonArray*>(pVal)) != nullptr) {
            std::string value = pJsonAry->toLuaString();
            luaStr.append(value);
        }
        
        if (i < num - 1) {
            luaStr.append(",");
            luaStr.append("\n");
        }
    }
    // ending
    luaStr.append("\n}");
    return luaStr;
}

MW_FRAMEWORK_END