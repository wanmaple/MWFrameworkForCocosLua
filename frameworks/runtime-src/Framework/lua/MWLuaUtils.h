/******************************
 Description: Lua operation helper.
 Author: M.Wan
 Date: 2/2/2015
 ******************************/

#ifndef __LUA_LUAUTILS__
#define __LUA_LUAUTILS__

#include "../base/mwbase.h"
#include <vector>
#include <string>

MW_FRAMEWORK_BEGIN

/**
 * Lua operation helper class.
 */
class MW_DLL MWLuaUtils
{
    MW_SINGLETON(MWLuaUtils);
public:
    /**
     * Get lua search paths.
     *
     * @return All package paths as a string.
     */
    std::string getPackagePath();
    
    /**
     * Add new lua search paths.
     *
     * @param paths Set lua search paths.
     */
    void addPackagePaths(const std::vector<std::string> &paths);
    
    /**
     * Execute a lua script.
     *
     * @param filePath The script to run.
     */
    void executeScriptFile(const std::string &filePath);
    
    /**
     * Set value of the specified key of a lua table.
     *
     * @param tableName Lua table name.
     * @param key Table key.
     * @param value The value you would like to set.
     * @param valueType Lua usertype name.
     */
    void setTableField(const std::string &tableName, const std::string &key, cocos2d::Ref *value, const std::string &valueType);
    
    /**
     * Execute a child function in the specified table.
     *
     * @param tableName Lua table name.
     * @param functionName The function name.
     * @param params Function parameters.
     * @param paramTypes Function parameter usertype names.
     * @param hasReturnValue Whether the function has return value.
     */
    void *executeTableFunction(const std::string &tableName, const std::string &functionName, MWArrayList *params, MWArrayList *paramTypes, bool hasReturnValue);
    
    /**
     * Execute a peertable function.
     *
     * @param userdata The related userdata of the peertable.
     * @param functionName The function name.
     * @param params Function parameters.
     * @param paramTypes Function parameter usertype names.
     * @param hasReturnValue Whether the function has return value.
     */
    void *executePeertableFunction(cocos2d::Ref *userdata, const std::string &functionName, MWArrayList *params, MWArrayList *paramTypes, bool hasReturnValue);
    
protected:
    void setPackagePath(const std::string &path);
    
    bool hasPeertable(void *userdata);
    
    bool hasFunction(void *userdata, const std::string &functionName);
    
    void *executeFunction(MWArrayList *params, MWArrayList *paramTypes, bool hasReturnValue);
};

MW_FRAMEWORK_END

#endif /* defined(__LUA_LUAUTILS__) */
