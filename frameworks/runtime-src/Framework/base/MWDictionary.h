/******************************
 Description: Dictionary structure.
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __BASE_DICTIONARY__
#define __BASE_DICTIONARY__

#include "base/CCRef.h"
#include "FrameworkMacros.h"
#include "ICloneable.h"
#include <unordered_map>
#include <vector>
#include <string>

MW_FRAMEWORK_BEGIN

class MWMutex;

/**
 * Dictionary data structure.
 */
class MW_DLL MWDictionary : public cocos2d::Ref, public ICloneable<MWDictionary>
{
public:
    /**
     * Create a dictionary structure.
     *
     * @return MWDictionary instance which is autoreleased.
     */
    static MWDictionary *create();
    
    /**
     * MWDictionary constructor.
     */
    MWDictionary();
    /**
     * MWDictionary destructor.
     */
    virtual ~MWDictionary();
    
    /**
     * Get the unordered array of all keys.
     *
     * @return Array of all keys(unordered).
     */
    std::vector<const std::string> allKeys();
    
    /**
     * Overload methods to set new value to the specified key.
     * @note If the key doesn't exist, it will generate a new pair to the map.
     *
     * @param key Dictionary key.
     * @param val Dictionary value.
     */
    void setObjectForKey(const std::string &key, double val);
    void setObjectForKey(const std::string &key, bool val);
    void setObjectForKey(const std::string &key, const std::string &val);
    void setObjectForKey(const std::string &key, cocos2d::Ref *val);
    
    /**
     * Get the value of the specified key, it will throw an exception if the key doesn't exist.
     *
     * @param key Dictionary key to consult.
     *
     * @return Dictionary value.
     */
    double numberForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    bool booleanForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    std::string stringForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    cocos2d::Ref *objectForKey(const std::string &key) MW_NOEXCEPTION(MW_WHETHER_THROW_EXCEPTION);
    
    /**
     * Remove the pair of the specified key, you will get a false if there is no such key.
     *
     * @param key Dictionary key to remove.
     *
     * @return Remove result.
     */
    bool removeObjectForKey(const std::string &key);
    /**
     * Clear all objects of the map.
     */
    void clear();
    
    /**
     * Whether the map contains the specified key?
     */
    bool hasKey(const std::string &key);
    
    /**
     * Get the pairs count of the map.
     */
    inline MW_UINT count()
    {
        return _innerMap.size();
    }
    /**
     * Whether the map is empty?
     */
    inline bool empty()
    {
        return _innerMap.empty();
    }
    
    /**
     * ICloneable overrides.
     */
    virtual MWDictionary *clone() override;
    
protected:
    std::unordered_map<std::string, cocos2d::Ref*> _innerMap;
};

MW_FRAMEWORK_END

#endif /* defined(__BASE_DICTIONARY__) */
