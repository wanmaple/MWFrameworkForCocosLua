/******************************
 Description: JSON elements classes.
 Author: M.Wan
 Date: 2/16/2015
 ******************************/

#ifndef __JSON_JSON_ELEMENT__
#define __JSON_JSON_ELEMENT__

#include "../base/mwbase.h"
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Json element base class.
 */
class IJsonElement
{
public:
    /**
     * JsonElement destructor.
     */
    virtual ~IJsonElement() {}
    
    /**
     * Return boolean value.
     */
    virtual bool boolValue() = 0;
    /**
     * Return number value.
     */
    virtual double numberValue() = 0;
    /**
     * Return string value.
     */
    virtual const char *stringValue() = 0;
};

class MW_DLL MWJsonBoolean : public MWObject, public IJsonElement, public IUninheritable<MWJsonBoolean>
{
public:
    /**
     * Create json boolean element.
     *
     * @param value Boolean value.
     *
     * @return Return boolean json element.
     */
    static MWJsonBoolean *create(bool value);
    
    /**
     * JsonBoolean constructor.
     *
     * @param value Boolean value.
     */
    MWJsonBoolean(bool value);
    
    /**
     * Return exact value.
     *
     * @return Boolean value.
     */
    bool boolValue();
    /**
     * Return 1 or 0.
     *
     * @return True to 1, False to 0.
     */
    double numberValue();
    /**
     * Return string value.
     *
     * @return True to "true", False to "false".
     */
    const char *stringValue();
    
private:
    bool _val;
};

class MW_DLL MWJsonNumber : public MWObject, public IJsonElement, public IUninheritable<MWJsonNumber>
{
public:
    /**
     * Create json number element.
     *
     * @param value Number value.
     *
     * @return Return number json element.
     */
    static MWJsonNumber *create(double value);
    
    /**
     * JsonNumber constructor.
     *
     * @param value Number value.
     */
    MWJsonNumber(double value);
    
    /**
     * Return true if the number is a non-zero value.
     *
     * @return Non-zero to true, zero to false.
     */
    bool boolValue();
    /**
     * Return exact number.
     *
     * @return Number value.
     */
    double numberValue();
    /**
     * Return string format of number.
     *
     * @return String of number.
     */
    const char *stringValue();
    
private:
    double _val;
};

class MW_DLL MWJsonString : public MWObject, public IJsonElement, public IUninheritable<MWJsonString>
{
public:
    /**
     * Create json string element.
     *
     * @param value String value.
     *
     * @return Return string json element.
     */
    static MWJsonString *create(const std::string &value);
    
    /**
     * JsonString constructor.
     *
     * @param value String value.
     */
    MWJsonString(const std::string &value);
    
    /**
     * Return true if it's not an empty string.
     *
     * @return Non-empty string to true, otherwise false.
     */
    bool boolValue();
    /**
     * Return exact number.
     *
     * @return Number value.
     */
    double numberValue();
    /**
     * Return string format of number.
     *
     * @return String of number.
     */
    const char *stringValue();
    
private:
    std::string _val;
};

MW_FRAMEWORK_END

#endif /* defined(__JSON_JSON_ELEMENT__) */
