/******************************
 Description: Dictionary structure.
 Author: M.Wan
 Date: 1/28/2015
 ******************************/

#ifndef __BASE_DICTIONARY__
#define __BASE_DICTIONARY__

#include "base/CCRef.h"
#include "../base/Macros.h"
#include <unordered_map>
#include <vector>
#include <string>

namespace mwframework {
    class MWDictionary : public cocos2d::Ref
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
        double numberForKey(const std::string &key);
        bool booleanForKey(const std::string &key);
        std::string stringForKey(const std::string &key);
        cocos2d::Ref *objectForKey(const std::string &key);
        
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
         * Get the pairs count of the map.
         */
        MW_UINT count();
        
    protected:
        std::unordered_map<std::string, cocos2d::Ref*> _innerMap;
    };
}

#endif /* defined(__BASE_DICTIONARY__) */
