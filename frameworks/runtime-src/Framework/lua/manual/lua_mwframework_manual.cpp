#include "lua_mwframework_manual.hpp"
#include "mwframework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include <vector>

MW_LOCAL int tolua_mwframework_MWDictionary_allKeys(lua_State *tolua_S)
{
    if (!tolua_S)
        return 0;
    
    int argc = 0;
    bool ok  = true;
    mwframework::MWDictionary *cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "mw.Dictionary", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (mwframework::MWDictionary *) tolua_tousertype(tolua_S, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_mwframework_MWDictionary_allKeys'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        
        std::vector<const std::string> ret = cobj->allKeys();
        
        lua_newtable(tolua_S);
        
        if (ret.empty())
            return 1;
        
        auto iter = ret.begin();
        int  indexTable = 1;
        for ( ; iter != ret.end(); ++iter)
        {
            lua_pushnumber(tolua_S, (lua_Number) indexTable);
            tolua_pushstring(tolua_S, (*iter).c_str());
            lua_rawset(tolua_S, -3);
            ++indexTable;
        }
        
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.MWDictionary:allKeys", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWDictionary_allKeys'.", &tolua_err);
#endif
    return 0;
}

MW_LOCAL int tolua_mwframework_MWGameScene_createWithParams(lua_State *tolua_S)
{
    if (!tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S, 1, "mw.GameScene", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1) {
        if (!tolua_istable(tolua_S, 2, 0, &tolua_err)) {
            goto tolua_lerror;
        }
        
        auto params = mwframework::MWDictionary::create();
        
        std::string key;
        // push nil, to iterate table.
        lua_pushnil(tolua_S);       // L: usertable, params, nil
        while (lua_next(tolua_S, -2)) {
            // what's the value type?
            printf("%s - %s\n",
                   lua_typename(tolua_S, lua_type(tolua_S, -2)),
                   lua_typename(tolua_S, lua_type(tolua_S, -1)));
//            cocos2d::Ref *value = nullptr;
//            if (tolua_isnumber(tolua_S, -1, 0, &tolua_err)) {
//                value = __Double::create(tolua_tonumber(tolua_S, -1, 0));
//            } else if (tolua_isboolean(tolua_S, -1, 0, &tolua_err)) {
//                value = __Bool::create(tolua_toboolean(tolua_S, -1, 0));
//            } else if (tolua_isstring(tolua_S, -1, 0, &tolua_err)) {
//                value = __String::create(tolua_tostring(tolua_S, -1, nullptr));
//            } else if (tolua_isusertype(tolua_S, -1, "cc.Ref", 0, &tolua_err)) {
//                value = (cocos2d::Ref *) tolua_tousertype(tolua_S, -1, nullptr);
//            } else {
//                continue;
//            }
//            
//            lua_pop(tolua_S, 1);
//            
//            // we only consider string keys.
//            if (tolua_isstring(tolua_S, -1, 0, &tolua_err)) {
//                lua_pushvalue(tolua_S, -1);
//                key = tolua_tostring(tolua_S, -1, nullptr);
//                printf("KEY: %s\n", key.c_str());
//                
//                if (value) {
//                    params->setObjectForKey(key, value);
//                }
//            } else {
//                continue;
//            }
            
            lua_pop(tolua_S, 1);
        }
        
        lua_pop(tolua_S, 1);
        
        auto ret = mwframework::MWGameScene::createWithParams(params);
        object_to_luaval<mwframework::MWGameScene>(tolua_S, "mw.GameScene", (mwframework::MWGameScene *) ret);
        return 1;
    }
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWGameScene_createWithParams'.", &tolua_err);
#endif
    return 0;
}

MW_LOCAL void extendMWDictionary(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "mw.Dictionary");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1)) {
        lua_pushstring(tolua_S, "allKeys");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWDictionary_allKeys);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

MW_LOCAL void extendMWGameScene(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "mw.GameScene");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1)) {
        lua_pushstring(tolua_S, "createWithParams");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWGameScene_createWithParams);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

TOLUA_API int register_all_mwframework_manual(lua_State *tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S, "mw", 0);
	tolua_beginmodule(tolua_S, "mw");

    extendMWDictionary(tolua_S);
    extendMWGameScene(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

