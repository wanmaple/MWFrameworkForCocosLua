#include "lua_mwframework_manual.hpp"
#include "mwframework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include <vector>

/******** MWDictionary extension ********/
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
        
        auto ret = cobj->allKeys();
        
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:allKeys", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWDictionary_allKeys'.", &tolua_err);
#endif
    return 0;
}

/******** MWGameScene extension ********/
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
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 2, 0, &tolua_err)) {
            goto tolua_lerror;
        }
#endif
        
        tolua_Error err;
        auto params = mwframework::MWDictionary::create();
        
        std::string key;
        // push nil, to iterate table.
        lua_pushnil(tolua_S);       // L: usertable, params, nil
        while (lua_next(tolua_S, -2)) {
            // what's the value type?
//            printf("%s - %s\n",
//                   lua_typename(tolua_S, lua_type(tolua_S, -2)),
//                   lua_typename(tolua_S, lua_type(tolua_S, -1)));
            cocos2d::Ref *value = nullptr;
            if (tolua_isnumber(tolua_S, 4, 0, &err)) {
                value = __Double::create(tolua_tonumber(tolua_S, -1, 0));
            } else if (tolua_isboolean(tolua_S, 4, 0, &err)) {
                value = __Bool::create(tolua_toboolean(tolua_S, -1, 0));
            } else if (tolua_isstring(tolua_S, 4, 0, &err)) {
                value = __String::create(tolua_tostring(tolua_S, -1, nullptr));
            } else if (tolua_isusertype(tolua_S, 4, "cc.Ref", 0, &err)) {
                value = static_cast<cocos2d::Ref *>(tolua_tousertype(tolua_S, -1, nullptr));
            }
            
            lua_pop(tolua_S, 1);
            
            // we only consider string keys.
            if (tolua_isstring(tolua_S, -1, 0, &err)) {
                lua_pushvalue(tolua_S, -1);
                key = tolua_tostring(tolua_S, -1, nullptr);
//                printf("KEY: %s\n", key.c_str());
                
                if (value) {
                    params->setObjectForKey(key, value);
                }
            }
            
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

/******** MWJsonObject extension ********/
MW_LOCAL int tolua_mwframework_MWJsonObject_allKeys(lua_State *tolua_S)
{
    if (!tolua_S)
        return 0;
    
    int argc = 0;
    bool ok  = true;
    mwframework::MWJsonObject *cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "mw.JsonObject", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (mwframework::MWJsonObject *) tolua_tousertype(tolua_S, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_mwframework_MWJsonObject_allKeys'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        
        auto ret = cobj->allKeys();
        
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:allKeys", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWJsonObject_allKeys'.", &tolua_err);
#endif
    return 0;
}

/******** MWSqliteDb extension ********/
MW_LOCAL int tolua_mwframework_MWSqliteDb_executeQuery(lua_State *tolua_S)
{
    if (!tolua_S)
        return 0;
    
    int argc = 0;
    bool ok  = true;
    mwframework::MWSqliteDb *cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "mw.SqliteDb", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (mwframework::MWSqliteDb *) tolua_tousertype(tolua_S, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_mwframework_MWSqliteDb_executeQuery'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        if(!ok)
            return 0;
        
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2, &arg0, "mw.SqliteDb:executeQuery");
        if (!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSqliteDb_executeQuery'", nullptr);
            return 0;
        }
        
        mwframework::MWArrayList *ret = cobj->executeQuery(arg0);
        
        lua_newtable(tolua_S);      // L: userdata, array
        
        for (int i = 0; i < ret->count(); ++i) {
            lua_pushnumber(tolua_S, i + 1);     // L: userdata, array, index
            lua_newtable(tolua_S);      // L: userdata, array, index, dict
            
            mwframework::MWDictionary *pDict = static_cast<mwframework::MWDictionary *>(ret->objectAtIndex(i));
            auto keys = pDict->allKeys();
            for (auto key : keys) {
                lua_pushstring(tolua_S, key.c_str());       // L: userdata, array, index, dict, key
                cocos2d::Ref *pVal = pDict->objectForKey(key);
                __Integer *pNum = nullptr;
                __Double *pNum2 = nullptr;
                __String *pStr = nullptr;
                if ((pNum = dynamic_cast<__Integer *>(pVal)) || (pNum2 = dynamic_cast<__Double *>(pVal))) {
                    double val;
                    if (pNum) {
                        val = pNum->getValue();
						lua_pushinteger(tolua_S, val);       // L: userdata, array, index, dict, key, val
                    } else if (pNum2) {
						val = pNum2->getValue();
						lua_pushnumber(tolua_S, val);       // L: userdata, array, index, dict, key, val
                    }
                    lua_rawset(tolua_S, -3);        // L: userdata, array, index, dict
                } else if ((pStr = dynamic_cast<__String *>(pDict->objectForKey(key)))) {
                    std::string val = pStr->getCString();
					// L: userdata, array, index, dict, key, val
					if (val == std::string("TRUE"))
					{
						lua_pushboolean(tolua_S, true);
					}
					else if (val == std::string("FALSE"))
					{
						lua_pushboolean(tolua_S, false);
					}
					else
					{
						lua_pushstring(tolua_S, val.c_str());
					}
                    lua_rawset(tolua_S, -3);    // L: userdata, array, index, dict
                } else {
					CCLOG("Invalid column value of %s", key.c_str());
					lua_pop(tolua_S, 1);
                }
            }
            lua_rawset(tolua_S, -3);        // L: userdata, array
        }
        
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SqliteDb:executeQuery", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWSqliteDb_executeQuery'.", &tolua_err);
#endif
    return 0;
}

/******** MWGifSprite extension ********/
MW_LOCAL int tolua_mwframework_MWGifSprite_getFrames(lua_State *tolua_S)
{
    if (!tolua_S)
        return 0;
    
    int argc = 0;
    bool ok  = true;
    mwframework::MWGifSprite *cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "mw.GifSprite", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (mwframework::MWGifSprite *) tolua_tousertype(tolua_S, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_mwframework_MWGifSprite_getFrames'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        
        mwframework::MWArrayList *ret = cobj->getFrames();
        
        lua_newtable(tolua_S);
        
        if (ret->empty())
            return 1;
        
        for (int i = 0; i < ret->count(); ++i) {
            lua_pushnumber(tolua_S, i + 1);
            tolua_pushusertype(tolua_S, ret->objectAtIndex(i), "mw.GifFrame");
            lua_rawset(tolua_S, -3);
        }
        
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:getFrames", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWGifSprite_getFrames'.", &tolua_err);
#endif
    return 0;
}

/******** MWAStarPathFinder extension ********/
MW_LOCAL int tolua_mwframework_MWAStarPathFinder_getFoundPath(lua_State *tolua_S)
{
	if (!tolua_S)
		return 0;

	int argc = 0;
	bool ok = true;
	mwframework::MWAStarPathFinder *cobj = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "mw.AStarPathFinder", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (mwframework::MWAStarPathFinder *) tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'tolua_mwframework_MWAStarPathFinder_getFoundPath'", NULL);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
			return 0;

		std::vector<cocos2d::Point> ret = cobj->getFoundPath();

		points_to_luaval(tolua_S, &ret[0], ret.size());

		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AStarPathFinder:getFoundPath", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWAStarPathFinder_getFoundPath'.", &tolua_err);
#endif
	return 0;
}

MW_LOCAL int tolua_mwframework_MWAStarPathFinder_setScriptDelegate(lua_State *tolua_S)
{
	int argc = 0;
	mwframework::MWAStarPathFinder *cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "mw.AStarPathFinder", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (mwframework::MWAStarPathFinder*) tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'tolua_mwframework_MWAStarPathFinder_setScriptDelegate'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		cocos2d::Ref *arg0;

		ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref", &arg0);
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'tolua_mwframework_MWAStarPathFinder_setScriptDelegate'", nullptr);
			return 0;
		}
		cobj->setScriptDelegate(arg0);
		return 0;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AStarPathFinder:setScriptDelegate", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWAStarPathFinder_setScriptDelegate'.", &tolua_err);
#endif

	return 0;
}

/******** MWAssetManager extension ********/
#if MW_ENABLE_SCRIPT_BINDING

MW_LOCAL int tolua_mwframework_MWAssetManager_getScriptDelegate(lua_State *tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager *cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "mw.AssetManager", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (mwframework::MWAssetManager*) tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'tolua_mwframework_MWAssetManager_getScriptDelegate'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S, "invalid arguments in function 'tolua_mwframework_MWAssetManager_getScriptDelegate'", nullptr);
            return 0;
        }
        cocos2d::Ref *ret = cobj->getScriptDelegate();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref", (cocos2d::Ref*) ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:getScriptDelegate", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_mwframework_MWAssetManager_getScriptDelegate'.", &tolua_err);
#endif
    
    return 0;
}

MW_LOCAL int tolua_mwframework_MWAssetManager_setScriptDelegate(lua_State *tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager *cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "mw.AssetManager", 0, &tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (mwframework::MWAssetManager*) tolua_tousertype(tolua_S, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'tolua_mwframework_MWAssetManager_setScriptDelegate'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        cocos2d::Ref *arg0;
        
        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref", &arg0);
        if (!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'tolua_mwframework_MWAssetManager_setScriptDelegate'", nullptr);
            return 0;
        }
        cobj->setScriptDelegate(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:setScriptDelegate", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_setScriptDelegate'.", &tolua_err);
#endif
    
    return 0;
}

#endif

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

MW_LOCAL void extendMWJsonObject(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "mw.JsonObject");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1)) {
        lua_pushstring(tolua_S, "allKeys");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWJsonObject_allKeys);
        lua_rawset(tolua_S, -3);
    }
}

MW_LOCAL void extendMWSqliteDb(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "mw.SqliteDb");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1)) {
        lua_pushstring(tolua_S, "executeQuery");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWSqliteDb_executeQuery);
        lua_rawset(tolua_S, -3);
    }
}

MW_LOCAL void extendMWGifSprite(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "mw.GifSprite");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1)) {
        lua_pushstring(tolua_S, "getFrames");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWGifSprite_getFrames);
        lua_rawset(tolua_S, -3);
    }
}

MW_LOCAL void extendMWAStarPathFinder(lua_State *tolua_S)
{
	lua_pushstring(tolua_S, "mw.AStarPathFinder");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1)) {
		lua_pushstring(tolua_S, "getFoundPath");
		lua_pushcfunction(tolua_S, tolua_mwframework_MWAStarPathFinder_getFoundPath);
		lua_rawset(tolua_S, -3);
		lua_pushstring(tolua_S, "setScriptDelegate");
		lua_pushcfunction(tolua_S, tolua_mwframework_MWAStarPathFinder_setScriptDelegate);
		lua_rawset(tolua_S, -3);
	}
}

#if MW_ENABLE_SCRIPT_BINDING

MW_LOCAL void extendMWAssetManager(lua_State *tolua_S)
{
    lua_pushstring(tolua_S, "mw.AssetManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1)) {
        lua_pushstring(tolua_S, "getScriptDelegate");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWAssetManager_getScriptDelegate);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setScriptDelegate");
        lua_pushcfunction(tolua_S, tolua_mwframework_MWAssetManager_setScriptDelegate);
        lua_rawset(tolua_S, -3);
    }
}

#endif

TOLUA_API int register_all_mwframework_manual(lua_State *tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S, "mw", 0);
	tolua_beginmodule(tolua_S, "mw");

    extendMWDictionary(tolua_S);
    extendMWGameScene(tolua_S);
    extendMWJsonObject(tolua_S);
    extendMWSqliteDb(tolua_S);
    extendMWGifSprite(tolua_S);
	extendMWAStarPathFinder(tolua_S);
#if MW_ENABLE_SCRIPT_BINDING
    extendMWAssetManager(tolua_S);
#endif

	tolua_endmodule(tolua_S);
	return 1;
}

