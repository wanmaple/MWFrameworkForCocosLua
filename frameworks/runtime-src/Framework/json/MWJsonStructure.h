/******************************
 Description: JSON elements classes.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONSTRUCTURE__
#define __JSON_JSONSTRUCTURE__

#include "../base/mwbase.h"
#include <string>
#include <vector>

#include "base/CCRef.h"

MW_FRAMEWORK_BEGIN

class MWJsonArray;
class MWJsonObject;

class MW_DLL MWJsonObject : public MWObject
{
    friend class MWJsonFormatter;
public:
    /**
     * JsonObject destructor
     */
    ~MWJsonObject();
    
    /**
     * Create an empty json object.
     */
    CREATE_FUNC(MWJsonObject);
    
    /**
     * Create a json object through string.
     *
     * @param jsonStr Json string.
     *
     * @return Return a new json object.
     */
    static MWJsonObject *createWithString(const std::string &jsonStr);
    /**
     * Create a json object from json file.
     *
     * @param jsonPath Json file path.
     *
     * @return Return a new json object.
     */
    static MWJsonObject *createWithFile(const std::string &jsonPath);
    
    /**
     * Figure out whether json has the specified key.
     *
     * @param key Key to consult.
     *
     * @return Whether the key exists.
     */
    bool hasKey(const std::string &key);
    
    /**
     * Get pairs count of json.
     *
     * @return Return the count of key-value pairs.
     */
    MW_UINT count();
    
    /**
     * Add new boolean value to json.
     *
     * @param key Key to insert.
     * @param value Boolean value to add.
     */
    void putBoolean(const std::string &key, bool value);
    /**
     * Return boolean of the specified key.
     *
     * @param key Key to consult.
     *
     * @return Return boolean value of key.
     */
    bool getBoolean(const std::string &key) const;
    
    /**
     * Add new number value to json.
     *
     * @param key Key to insert.
     * @param value Number value to add.
     */
    void putNumber(const std::string &key, double value);
    /**
     * Return number of the specified key.
     *
     * @param key Key to consult.
     *
     * @return Return number value of key.
     */
    double getNumber(const std::string &key) const;
    
    /**
     * Add new string value to json.
     *
     * @param key Key to insert.
     * @param value String value to add.
     */
    void putString(const std::string &key, const std::string &value);
    /**
     * Return string of the specified key.
     *
     * @param key Key to consult.
     *
     * @return Return string value of key.
     */
    const char *getString(const std::string &key) const;
    
    /**
     * Add new json object to json.
     *
     * @param key Key to insert.
     * @param value Json object to add.
     */
    void putJsonObject(const std::string &key, MWJsonObject *value);
    /**
     * Get json object of the specified key.
     *
     * @param key Key to consult.
     *
     * @return Return json object of key.
     */
    MWJsonObject *getJsonObject(const std::string &key) const;
    
    /**
     * Add new json array to json.
     *
     * @param key Key to insert.
     * @param value Json array to add.
     */
    void putJsonArray(const std::string &key, MWJsonArray *value);
    /**
     * Get json array of the specified key.
     *
     * @param key Key to consult.
     *
     * @return Return json array of key.
     */
    MWJsonArray *getJsonArray(const std::string &key) const;
    
    /**
     * Get any object of the specified key.
     *
     * @param key Key to consult.
     *
     * @return Return object of key.
     */
    MWObject *getObject(const std::string &key) const;
    
    /**
     * Remove value of the specified key.
     *
     * @param key Key to remove.
     */
    void remove(const std::string &key);
    
    /**
     * Clear json.
     */
    void clear();
    
    /**
     * Get keys of the json.
     *
     * @return All key collection of json.
     */
    std::vector<std::string> allKeys();
    
    /**
     * Convert to json string.
     *
     * @return Return json string format.
     */
    virtual std::string toString() override;
    /**
     * Convert to pretty string.
     *
     * @return Return pretty version of json string.
     */
    std::string toPrettyString();
    /**
     * Convert to lua string.
     *
     * @return Return lua version of json string.
     */
    std::string toLuaString();
    
protected:
    bool init();
    
    MWJsonObject();
    
    MWDictionary *_dataHolder;
};

class MW_DLL MWJsonArray : public MWObject
{
    friend class MWJsonFormatter;
public:
    /**
     * JsonArray destructor
     */
    ~MWJsonArray();
    
    /**
     * Create an empty json array.
     */
    CREATE_FUNC(MWJsonArray);
    
    /**
     * Create a json array through string.
     *
     * @param jsonStr Json string.
     *
     * @return Return a new json array.
     */
    static MWJsonArray *createWithString(const std::string &jsonStr);
    /**
     * Create a json array from json file.
     *
     * @param jsonPath Json file path.
     *
     * @return Return a new json array.
     */
    static MWJsonArray *createWithFile(const std::string &jsonPath);
    
    /**
     * Get json elements count of array.
     *
     * @return Return the count of array.
     */
    MW_UINT count();
    
    /**
     * Append a boolean value to the array tail.
     *
     * @param value Boolean value.
     */
    void appendBoolean(bool value);
    /**
     * Insert a boolean value at the specified index.
     *
     * @param value Boolean value.
     * @param index Specified index.
     */
    void insertBoolean(bool value, MW_UINT index);
    /**
     * Get boolean value at specified index.
     *
     * @param index Index to consult.
     *
     * @return Specified value.
     */
    bool getBooleanAt(int index);
    
    /**
     * Append a number value to the array tail.
     *
     * @param value Number value.
     */
    void appendNumber(double value);
    /**
     * Insert a number value at the specified index.
     *
     * @param value Number value.
     * @param index Specified index.
     */
    void insertNumber(double value, MW_UINT index);
    /**
     * Get number value at specified index.
     *
     * @param index Index to consult.
     *
     * @return Specified value.
     */
    double getNumberAt(MW_UINT index);
    
    /**
     * Append a string value to the array tail.
     *
     * @param value String value.
     */
    void appendString(const std::string &value);
    /**
     * Insert a string value at the specified index.
     *
     * @param value String value.
     * @param index Specified index.
     */
    void insertString(const std::string &value, int index);
    /**
     * Get string value at specified index.
     *
     * @param index Index to consult.
     *
     * @return Specified value.
     */
    const char *getStringAt(MW_UINT index);
    
    /**
     * Append a json object to the array tail.
     *
     * @param value Json object.
     */
    void appendJsonObject(MWJsonObject *value);
    /**
     * Insert a json object at the specified index.
     *
     * @param value Json object.
     * @param index Specified index.
     */
    void insertJsonObject(MWJsonObject *value, MW_UINT index);
    /**
     * Get json object at specified index.
     *
     * @param index Index to consult.
     *
     * @return Specified value.
     */
    MWJsonObject *getJsonObjectAt(MW_UINT index);
    
    /**
     * Append a json array to the array tail.
     *
     * @param value Json array.
     */
    void appendJsonArray(MWJsonArray *value);
    /**
     * Insert a json array at the specified index.
     *
     * @param value Json array.
     * @param index Specified index.
     */
    void insertJsonArray(MWJsonArray *value, MW_UINT index);
    /**
     * Get json array at specified index.
     *
     * @param index Index to consult.
     *
     * @return Specified value.
     */
    MWJsonArray *getJsonArrayAt(MW_UINT index);
    
    /**
     * Get any object at specified index.
     *
     * @param index Index to consult.
     *
     * @return Specified value.
     */
    MWObject *getObjectAt(MW_UINT index);
    
    /**
     * Remove the object at specified index.
     *
     * @param index Index to remove.
     */
    void removeAt(MW_UINT index);
    
    /**
     * Clear all array elements.
     */
    void clear();
    
    /**
     * Convert to json string.
     *
     * @return Return json string format.
     */
    virtual std::string toString() override;
    /**
     * Convert to pretty string.
     *
     * @return Return pretty version of json string.
     */
    std::string toPrettyString();
    /**
     * Convert to lua string.
     *
     * @return Return lua version of json string.
     */
    std::string toLuaString();
    
protected:
    bool init();
    
    MWJsonArray();
    
    MWArrayList *_dataHolder;
};

MW_FRAMEWORK_END

#endif /* defined(__JSON_JSONSTRUCTURE__) */
