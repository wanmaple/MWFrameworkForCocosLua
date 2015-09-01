#include "lua_mwframework_auto.hpp"
#include "mwframework.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_mwframework_MWObject_toString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Object",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWObject_toString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWObject_toString'", nullptr);
            return 0;
        }
        std::string ret = cobj->toString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Object:toString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWObject_toString'.",&tolua_err);
#endif

    return 0;
}
static int lua_mwframework_MWObject_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWObject)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.Object",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWObject* self = (mwframework::MWObject*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWObject(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.Object");
    tolua_cclass(tolua_S,"Object","mw.Object","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Object");
        tolua_function(tolua_S,"toString",lua_mwframework_MWObject_toString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWObject).name();
    g_luaType[typeName] = "mw.Object";
    g_typeCast["Object"] = "mw.Object";
    return 1;
}

int lua_mwframework_MWBinaryData_isValid(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWBinaryData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.BinaryData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWBinaryData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWBinaryData_isValid'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWBinaryData_isValid'", nullptr);
            return 0;
        }
        bool ret = cobj->isValid();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.BinaryData:isValid",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWBinaryData_isValid'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWBinaryData_toString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWBinaryData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.BinaryData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWBinaryData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWBinaryData_toString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWBinaryData_toString'", nullptr);
            return 0;
        }
        std::string ret = cobj->toString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.BinaryData:toString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWBinaryData_toString'.",&tolua_err);
#endif

    return 0;
}
static int lua_mwframework_MWBinaryData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWBinaryData)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.BinaryData",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWBinaryData* self = (mwframework::MWBinaryData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWBinaryData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.BinaryData");
    tolua_cclass(tolua_S,"BinaryData","mw.BinaryData","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"BinaryData");
        tolua_function(tolua_S,"isValid",lua_mwframework_MWBinaryData_isValid);
        tolua_function(tolua_S,"toString",lua_mwframework_MWBinaryData_toString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWBinaryData).name();
    g_luaType[typeName] = "mw.BinaryData";
    g_typeCast["BinaryData"] = "mw.BinaryData";
    return 1;
}

int lua_mwframework_MWException_errorCode(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWException* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Exception",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWException*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWException_errorCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWException_errorCode'", nullptr);
            return 0;
        }
        int ret = cobj->errorCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Exception:errorCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWException_errorCode'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWException_what(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWException* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Exception",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWException*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWException_what'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWException_what'", nullptr);
            return 0;
        }
        const char* ret = cobj->what();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Exception:what",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWException_what'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWException_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.Exception",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        const char* arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "mw.Exception:create");
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "mw.Exception:create"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWException_create'", nullptr);
            return 0;
        }
        mwframework::MWException* ret = mwframework::MWException::create(arg0, arg1);
        object_to_luaval<mwframework::MWException>(tolua_S, "mw.Exception",(mwframework::MWException*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.Exception:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWException_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWException_constructor(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWException* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        const char* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "mw.Exception:MWException");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "mw.Exception:MWException"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWException_constructor'", nullptr);
            return 0;
        }
        cobj = new mwframework::MWException(arg0, arg1);
        tolua_pushusertype(tolua_S,(void*)cobj,"mw.Exception");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Exception:MWException",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWException_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_mwframework_MWException_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWException)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.Exception",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWException* self = (mwframework::MWException*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWException(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.Exception");
    tolua_cclass(tolua_S,"Exception","mw.Exception","mw.Object",lua_mwframework_MWException_finalize);

    tolua_beginmodule(tolua_S,"Exception");
        tolua_function(tolua_S,"new",lua_mwframework_MWException_constructor);
        tolua_function(tolua_S,"errorCode",lua_mwframework_MWException_errorCode);
        tolua_function(tolua_S,"what",lua_mwframework_MWException_what);
        tolua_function(tolua_S,"create", lua_mwframework_MWException_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWException).name();
    g_luaType[typeName] = "mw.Exception";
    g_typeCast["Exception"] = "mw.Exception";
    return 1;
}

int lua_mwframework_MWDictionary_count(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_count'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_count'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->count();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:count",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_count'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_removeObjectForKey(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_removeObjectForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Dictionary:removeObjectForKey");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_removeObjectForKey'", nullptr);
            return 0;
        }
        bool ret = cobj->removeObjectForKey(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:removeObjectForKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_removeObjectForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_clear(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_setObjectForKey(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_setObjectForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::Ref* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Dictionary:setObjectForKey");

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_setObjectForKey'", nullptr);
            return 0;
        }
        cobj->setObjectForKey(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:setObjectForKey",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_setObjectForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_objectForKey(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_objectForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Dictionary:objectForKey");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_objectForKey'", nullptr);
            return 0;
        }
        cocos2d::Ref* ret = cobj->objectForKey(arg0);
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:objectForKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_objectForKey'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_empty(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_empty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_empty'", nullptr);
            return 0;
        }
        bool ret = cobj->empty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:empty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_empty'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_hasKey(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_hasKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Dictionary:hasKey");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_hasKey'", nullptr);
            return 0;
        }
        bool ret = cobj->hasKey(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:hasKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_hasKey'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_clone(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWDictionary*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWDictionary_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_clone'", nullptr);
            return 0;
        }
        mwframework::MWDictionary* ret = cobj->clone();
        object_to_luaval<mwframework::MWDictionary>(tolua_S, "mw.Dictionary",(mwframework::MWDictionary*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWDictionary_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.Dictionary",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_create'", nullptr);
            return 0;
        }
        mwframework::MWDictionary* ret = mwframework::MWDictionary::create();
        object_to_luaval<mwframework::MWDictionary>(tolua_S, "mw.Dictionary",(mwframework::MWDictionary*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.Dictionary:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWDictionary_constructor(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWDictionary* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWDictionary_constructor'", nullptr);
            return 0;
        }
        cobj = new mwframework::MWDictionary();
        tolua_pushusertype(tolua_S,(void*)cobj,"mw.Dictionary");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Dictionary:MWDictionary",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWDictionary_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_mwframework_MWDictionary_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWDictionary)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.Dictionary",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWDictionary* self = (mwframework::MWDictionary*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWDictionary(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.Dictionary");
    tolua_cclass(tolua_S,"Dictionary","mw.Dictionary","mw.Object",lua_mwframework_MWDictionary_finalize);

    tolua_beginmodule(tolua_S,"Dictionary");
        tolua_function(tolua_S,"new",lua_mwframework_MWDictionary_constructor);
        tolua_function(tolua_S,"count",lua_mwframework_MWDictionary_count);
        tolua_function(tolua_S,"removeObjectForKey",lua_mwframework_MWDictionary_removeObjectForKey);
        tolua_function(tolua_S,"clear",lua_mwframework_MWDictionary_clear);
        tolua_function(tolua_S,"setObjectForKey",lua_mwframework_MWDictionary_setObjectForKey);
        tolua_function(tolua_S,"objectForKey",lua_mwframework_MWDictionary_objectForKey);
        tolua_function(tolua_S,"empty",lua_mwframework_MWDictionary_empty);
        tolua_function(tolua_S,"hasKey",lua_mwframework_MWDictionary_hasKey);
        tolua_function(tolua_S,"clone",lua_mwframework_MWDictionary_clone);
        tolua_function(tolua_S,"create", lua_mwframework_MWDictionary_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWDictionary).name();
    g_luaType[typeName] = "mw.Dictionary";
    g_typeCast["Dictionary"] = "mw.Dictionary";
    return 1;
}

int lua_mwframework_MWArrayList_count(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_count'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_count'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->count();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:count",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_count'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_setObjectAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_setObjectAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Ref* arg0;
        unsigned int arg1;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.ArrayList:setObjectAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_setObjectAtIndex'", nullptr);
            return 0;
        }
        cobj->setObjectAtIndex(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:setObjectAtIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_setObjectAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_removeObjectAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_removeObjectAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.ArrayList:removeObjectAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_removeObjectAtIndex'", nullptr);
            return 0;
        }
        bool ret = cobj->removeObjectAtIndex(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:removeObjectAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_removeObjectAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_appendObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_appendObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_appendObject'", nullptr);
            return 0;
        }
        cobj->appendObject(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:appendObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_appendObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_lastIndexOfObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_lastIndexOfObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_lastIndexOfObject'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->lastIndexOfObject(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:lastIndexOfObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_lastIndexOfObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_indexOfObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_indexOfObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_indexOfObject'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->indexOfObject(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:indexOfObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_indexOfObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_insertObjectAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_insertObjectAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Ref* arg0;
        unsigned int arg1;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.ArrayList:insertObjectAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_insertObjectAtIndex'", nullptr);
            return 0;
        }
        cobj->insertObjectAtIndex(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:insertObjectAtIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_insertObjectAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_removeObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_removeObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_removeObject'", nullptr);
            return 0;
        }
        bool ret = cobj->removeObject(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:removeObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_removeObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_clone(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_clone'", nullptr);
            return 0;
        }
        mwframework::MWArrayList* ret = cobj->clone();
        object_to_luaval<mwframework::MWArrayList>(tolua_S, "mw.ArrayList",(mwframework::MWArrayList*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_clear(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_empty(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_empty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_empty'", nullptr);
            return 0;
        }
        bool ret = cobj->empty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:empty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_empty'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_objectAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWArrayList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWArrayList_objectAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.ArrayList:objectAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_objectAtIndex'", nullptr);
            return 0;
        }
        cocos2d::Ref* ret = cobj->objectAtIndex(arg0);
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:objectAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_objectAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWArrayList_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.ArrayList",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_create'", nullptr);
            return 0;
        }
        mwframework::MWArrayList* ret = mwframework::MWArrayList::create();
        object_to_luaval<mwframework::MWArrayList>(tolua_S, "mw.ArrayList",(mwframework::MWArrayList*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.ArrayList:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWArrayList_constructor(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWArrayList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWArrayList_constructor'", nullptr);
            return 0;
        }
        cobj = new mwframework::MWArrayList();
        tolua_pushusertype(tolua_S,(void*)cobj,"mw.ArrayList");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ArrayList:MWArrayList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWArrayList_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_mwframework_MWArrayList_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWArrayList)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.ArrayList",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWArrayList* self = (mwframework::MWArrayList*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWArrayList(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.ArrayList");
    tolua_cclass(tolua_S,"ArrayList","mw.ArrayList","mw.Object",lua_mwframework_MWArrayList_finalize);

    tolua_beginmodule(tolua_S,"ArrayList");
        tolua_function(tolua_S,"new",lua_mwframework_MWArrayList_constructor);
        tolua_function(tolua_S,"count",lua_mwframework_MWArrayList_count);
        tolua_function(tolua_S,"setObjectAtIndex",lua_mwframework_MWArrayList_setObjectAtIndex);
        tolua_function(tolua_S,"removeObjectAtIndex",lua_mwframework_MWArrayList_removeObjectAtIndex);
        tolua_function(tolua_S,"appendObject",lua_mwframework_MWArrayList_appendObject);
        tolua_function(tolua_S,"lastIndexOfObject",lua_mwframework_MWArrayList_lastIndexOfObject);
        tolua_function(tolua_S,"indexOfObject",lua_mwframework_MWArrayList_indexOfObject);
        tolua_function(tolua_S,"insertObjectAtIndex",lua_mwframework_MWArrayList_insertObjectAtIndex);
        tolua_function(tolua_S,"removeObject",lua_mwframework_MWArrayList_removeObject);
        tolua_function(tolua_S,"clone",lua_mwframework_MWArrayList_clone);
        tolua_function(tolua_S,"clear",lua_mwframework_MWArrayList_clear);
        tolua_function(tolua_S,"empty",lua_mwframework_MWArrayList_empty);
        tolua_function(tolua_S,"objectAtIndex",lua_mwframework_MWArrayList_objectAtIndex);
        tolua_function(tolua_S,"create", lua_mwframework_MWArrayList_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWArrayList).name();
    g_luaType[typeName] = "mw.ArrayList";
    g_typeCast["ArrayList"] = "mw.ArrayList";
    return 1;
}

int lua_mwframework_MWQueue_count(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_count'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_count'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->count();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:count",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_count'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_dequeue(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_dequeue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_dequeue'", nullptr);
            return 0;
        }
        bool ret = cobj->dequeue();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:dequeue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_dequeue'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_clear(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_enqueue(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_enqueue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_enqueue'", nullptr);
            return 0;
        }
        cobj->enqueue(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:enqueue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_enqueue'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_front(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_front'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_front'", nullptr);
            return 0;
        }
        cocos2d::Ref* ret = cobj->front();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:front",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_front'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_clone(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_clone'", nullptr);
            return 0;
        }
        mwframework::MWQueue* ret = cobj->clone();
        object_to_luaval<mwframework::MWQueue>(tolua_S, "mw.Queue",(mwframework::MWQueue*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_empty(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWQueue*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWQueue_empty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_empty'", nullptr);
            return 0;
        }
        bool ret = cobj->empty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:empty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_empty'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWQueue_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.Queue",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_create'", nullptr);
            return 0;
        }
        mwframework::MWQueue* ret = mwframework::MWQueue::create();
        object_to_luaval<mwframework::MWQueue>(tolua_S, "mw.Queue",(mwframework::MWQueue*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.Queue:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWQueue_constructor(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWQueue* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWQueue_constructor'", nullptr);
            return 0;
        }
        cobj = new mwframework::MWQueue();
        tolua_pushusertype(tolua_S,(void*)cobj,"mw.Queue");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Queue:MWQueue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWQueue_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_mwframework_MWQueue_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWQueue)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.Queue",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWQueue* self = (mwframework::MWQueue*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWQueue(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.Queue");
    tolua_cclass(tolua_S,"Queue","mw.Queue","mw.Object",lua_mwframework_MWQueue_finalize);

    tolua_beginmodule(tolua_S,"Queue");
        tolua_function(tolua_S,"new",lua_mwframework_MWQueue_constructor);
        tolua_function(tolua_S,"count",lua_mwframework_MWQueue_count);
        tolua_function(tolua_S,"dequeue",lua_mwframework_MWQueue_dequeue);
        tolua_function(tolua_S,"clear",lua_mwframework_MWQueue_clear);
        tolua_function(tolua_S,"enqueue",lua_mwframework_MWQueue_enqueue);
        tolua_function(tolua_S,"front",lua_mwframework_MWQueue_front);
        tolua_function(tolua_S,"clone",lua_mwframework_MWQueue_clone);
        tolua_function(tolua_S,"empty",lua_mwframework_MWQueue_empty);
        tolua_function(tolua_S,"create", lua_mwframework_MWQueue_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWQueue).name();
    g_luaType[typeName] = "mw.Queue";
    g_typeCast["Queue"] = "mw.Queue";
    return 1;
}

int lua_mwframework_MWStack_count(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_count'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_count'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->count();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:count",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_count'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_top(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_top'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_top'", nullptr);
            return 0;
        }
        cocos2d::Ref* ret = cobj->top();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:top",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_top'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_pop(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_pop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_pop'", nullptr);
            return 0;
        }
        bool ret = cobj->pop();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:pop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_pop'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_push(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_push'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_push'", nullptr);
            return 0;
        }
        cobj->push(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:push",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_push'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_clone(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_clone'", nullptr);
            return 0;
        }
        mwframework::MWStack* ret = cobj->clone();
        object_to_luaval<mwframework::MWStack>(tolua_S, "mw.Stack",(mwframework::MWStack*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_clear(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_empty(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWStack*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWStack_empty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_empty'", nullptr);
            return 0;
        }
        bool ret = cobj->empty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:empty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_empty'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWStack_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.Stack",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_create'", nullptr);
            return 0;
        }
        mwframework::MWStack* ret = mwframework::MWStack::create();
        object_to_luaval<mwframework::MWStack>(tolua_S, "mw.Stack",(mwframework::MWStack*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.Stack:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWStack_constructor(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWStack* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWStack_constructor'", nullptr);
            return 0;
        }
        cobj = new mwframework::MWStack();
        tolua_pushusertype(tolua_S,(void*)cobj,"mw.Stack");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Stack:MWStack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWStack_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_mwframework_MWStack_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWStack)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.Stack",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWStack* self = (mwframework::MWStack*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWStack(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.Stack");
    tolua_cclass(tolua_S,"Stack","mw.Stack","mw.Object",lua_mwframework_MWStack_finalize);

    tolua_beginmodule(tolua_S,"Stack");
        tolua_function(tolua_S,"new",lua_mwframework_MWStack_constructor);
        tolua_function(tolua_S,"count",lua_mwframework_MWStack_count);
        tolua_function(tolua_S,"top",lua_mwframework_MWStack_top);
        tolua_function(tolua_S,"pop",lua_mwframework_MWStack_pop);
        tolua_function(tolua_S,"push",lua_mwframework_MWStack_push);
        tolua_function(tolua_S,"clone",lua_mwframework_MWStack_clone);
        tolua_function(tolua_S,"clear",lua_mwframework_MWStack_clear);
        tolua_function(tolua_S,"empty",lua_mwframework_MWStack_empty);
        tolua_function(tolua_S,"create", lua_mwframework_MWStack_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWStack).name();
    g_luaType[typeName] = "mw.Stack";
    g_typeCast["Stack"] = "mw.Stack";
    return 1;
}

int lua_mwframework_MWSystemHelper_checkNetStatus(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSystemHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SystemHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSystemHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSystemHelper_checkNetStatus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSystemHelper_checkNetStatus'", nullptr);
            return 0;
        }
        int ret = (int)cobj->checkNetStatus();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SystemHelper:checkNetStatus",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSystemHelper_checkNetStatus'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSystemHelper_getCurrentUsedMemory(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSystemHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SystemHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSystemHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSystemHelper_getCurrentUsedMemory'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSystemHelper_getCurrentUsedMemory'", nullptr);
            return 0;
        }
        double ret = cobj->getCurrentUsedMemory();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SystemHelper:getCurrentUsedMemory",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSystemHelper_getCurrentUsedMemory'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSystemHelper_millisecondsNow(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSystemHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SystemHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSystemHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSystemHelper_millisecondsNow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSystemHelper_millisecondsNow'", nullptr);
            return 0;
        }
        unsigned long ret = cobj->millisecondsNow();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SystemHelper:millisecondsNow",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSystemHelper_millisecondsNow'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSystemHelper_copyToPasteBoard(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSystemHelper* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SystemHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSystemHelper*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSystemHelper_copyToPasteBoard'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.SystemHelper:copyToPasteBoard");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSystemHelper_copyToPasteBoard'", nullptr);
            return 0;
        }
        cobj->copyToPasteBoard(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SystemHelper:copyToPasteBoard",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSystemHelper_copyToPasteBoard'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSystemHelper_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.SystemHelper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSystemHelper_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWSystemHelper* ret = mwframework::MWSystemHelper::getInstance();
        object_to_luaval<mwframework::MWSystemHelper>(tolua_S, "mw.SystemHelper",(mwframework::MWSystemHelper*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.SystemHelper:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSystemHelper_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWSystemHelper_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWSystemHelper)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.SystemHelper",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWSystemHelper* self = (mwframework::MWSystemHelper*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWSystemHelper(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.SystemHelper");
    tolua_cclass(tolua_S,"SystemHelper","mw.SystemHelper","",nullptr);

    tolua_beginmodule(tolua_S,"SystemHelper");
        tolua_function(tolua_S,"checkNetStatus",lua_mwframework_MWSystemHelper_checkNetStatus);
        tolua_function(tolua_S,"getCurrentUsedMemory",lua_mwframework_MWSystemHelper_getCurrentUsedMemory);
        tolua_function(tolua_S,"millisecondsNow",lua_mwframework_MWSystemHelper_millisecondsNow);
        tolua_function(tolua_S,"copyToPasteBoard",lua_mwframework_MWSystemHelper_copyToPasteBoard);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWSystemHelper_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWSystemHelper).name();
    g_luaType[typeName] = "mw.SystemHelper";
    g_typeCast["SystemHelper"] = "mw.SystemHelper";
    return 1;
}

int lua_mwframework_MWIOUtils_fileExists(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_fileExists'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:fileExists");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_fileExists'", nullptr);
            return 0;
        }
        bool ret = cobj->fileExists(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:fileExists",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_fileExists'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_copyFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_copyFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:copyFile");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.IOUtils:copyFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_copyFile'", nullptr);
            return 0;
        }
        bool ret = cobj->copyFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:copyFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_copyFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_writeDataToFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_writeDataToFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            mwframework::MWBinaryData* arg0;
            ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            bool ret = cobj->writeDataToFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            mwframework::MWBinaryData* arg0;
            ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            bool ret = cobj->writeDataToFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            const void* arg0;
            #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

            if (!ok) { break; }
            unsigned long arg1;
            ok &= luaval_to_ulong(tolua_S, 3, &arg1, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            std::string arg2;
            ok &= luaval_to_std_string(tolua_S, 4,&arg2, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            bool ret = cobj->writeDataToFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            const void* arg0;
            #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

            if (!ok) { break; }
            unsigned long arg1;
            ok &= luaval_to_ulong(tolua_S, 3, &arg1, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            std::string arg2;
            ok &= luaval_to_std_string(tolua_S, 4,&arg2, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "mw.IOUtils:writeDataToFile");

            if (!ok) { break; }
            bool ret = cobj->writeDataToFile(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "mw.IOUtils:writeDataToFile",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_writeDataToFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_getDataFromFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_getDataFromFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:getDataFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_getDataFromFile'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->getDataFromFile(arg0);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:getDataFromFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_getDataFromFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_splicePath(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_splicePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:splicePath");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.IOUtils:splicePath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_splicePath'", nullptr);
            return 0;
        }
        std::string ret = cobj->splicePath(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:splicePath",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_splicePath'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_createFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_createFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:createFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_createFile'", nullptr);
            return 0;
        }
        bool ret = cobj->createFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:createFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_createFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_resourcePath(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_resourcePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:resourcePath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_resourcePath'", nullptr);
            return 0;
        }
        std::string ret = cobj->resourcePath(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:resourcePath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_resourcePath'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_directoryExists(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_directoryExists'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:directoryExists");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_directoryExists'", nullptr);
            return 0;
        }
        bool ret = cobj->directoryExists(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:directoryExists",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_directoryExists'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_removeFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_removeFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:removeFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_removeFile'", nullptr);
            return 0;
        }
        bool ret = cobj->removeFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:removeFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_removeFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_moveFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_moveFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:moveFile");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.IOUtils:moveFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_moveFile'", nullptr);
            return 0;
        }
        bool ret = cobj->moveFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:moveFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_moveFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_removeDirectory(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_removeDirectory'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:removeDirectory");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_removeDirectory'", nullptr);
            return 0;
        }
        bool ret = cobj->removeDirectory(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:removeDirectory",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_removeDirectory'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_createDirectory(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWIOUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWIOUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWIOUtils_createDirectory'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.IOUtils:createDirectory");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_createDirectory'", nullptr);
            return 0;
        }
        bool ret = cobj->createDirectory(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.IOUtils:createDirectory",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_createDirectory'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWIOUtils_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.IOUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWIOUtils_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWIOUtils* ret = mwframework::MWIOUtils::getInstance();
        object_to_luaval<mwframework::MWIOUtils>(tolua_S, "mw.IOUtils",(mwframework::MWIOUtils*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.IOUtils:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWIOUtils_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWIOUtils_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWIOUtils)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.IOUtils",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWIOUtils* self = (mwframework::MWIOUtils*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWIOUtils(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.IOUtils");
    tolua_cclass(tolua_S,"IOUtils","mw.IOUtils","",nullptr);

    tolua_beginmodule(tolua_S,"IOUtils");
        tolua_function(tolua_S,"fileExists",lua_mwframework_MWIOUtils_fileExists);
        tolua_function(tolua_S,"copyFile",lua_mwframework_MWIOUtils_copyFile);
        tolua_function(tolua_S,"writeDataToFile",lua_mwframework_MWIOUtils_writeDataToFile);
        tolua_function(tolua_S,"getDataFromFile",lua_mwframework_MWIOUtils_getDataFromFile);
        tolua_function(tolua_S,"splicePath",lua_mwframework_MWIOUtils_splicePath);
        tolua_function(tolua_S,"createFile",lua_mwframework_MWIOUtils_createFile);
        tolua_function(tolua_S,"resourcePath",lua_mwframework_MWIOUtils_resourcePath);
        tolua_function(tolua_S,"directoryExists",lua_mwframework_MWIOUtils_directoryExists);
        tolua_function(tolua_S,"removeFile",lua_mwframework_MWIOUtils_removeFile);
        tolua_function(tolua_S,"moveFile",lua_mwframework_MWIOUtils_moveFile);
        tolua_function(tolua_S,"removeDirectory",lua_mwframework_MWIOUtils_removeDirectory);
        tolua_function(tolua_S,"createDirectory",lua_mwframework_MWIOUtils_createDirectory);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWIOUtils_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWIOUtils).name();
    g_luaType[typeName] = "mw.IOUtils";
    g_typeCast["IOUtils"] = "mw.IOUtils";
    return 1;
}

int lua_mwframework_MWGameScene_getViewControllers(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getViewControllers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getViewControllers'", nullptr);
            return 0;
        }
        mwframework::MWDictionary* ret = cobj->getViewControllers();
        object_to_luaval<mwframework::MWDictionary>(tolua_S, "mw.Dictionary",(mwframework::MWDictionary*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getViewControllers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getViewControllers'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_unloadViewController(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_unloadViewController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWViewController* arg0;

        ok &= luaval_to_object<mwframework::MWViewController>(tolua_S, 2, "mw.ViewController",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_unloadViewController'", nullptr);
            return 0;
        }
        cobj->unloadViewController(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:unloadViewController",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_unloadViewController'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_loadViewController(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_loadViewController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWViewController* arg0;
        std::string arg1;

        ok &= luaval_to_object<mwframework::MWViewController>(tolua_S, 2, "mw.ViewController",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.GameScene:loadViewController");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_loadViewController'", nullptr);
            return 0;
        }
        cobj->loadViewController(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:loadViewController",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_loadViewController'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_getViewControllerByIdentifier(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getViewControllerByIdentifier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:getViewControllerByIdentifier");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getViewControllerByIdentifier'", nullptr);
            return 0;
        }
        mwframework::MWViewController* ret = cobj->getViewControllerByIdentifier(arg0);
        object_to_luaval<mwframework::MWViewController>(tolua_S, "mw.ViewController",(mwframework::MWViewController*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getViewControllerByIdentifier",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getViewControllerByIdentifier'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_getBooleanParameter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getBooleanParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:getBooleanParameter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getBooleanParameter'", nullptr);
            return 0;
        }
        bool ret = cobj->getBooleanParameter(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getBooleanParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getBooleanParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_unloadAllViewControllers(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_unloadAllViewControllers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_unloadAllViewControllers'", nullptr);
            return 0;
        }
        cobj->unloadAllViewControllers();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:unloadAllViewControllers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_unloadAllViewControllers'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_addParameter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_addParameter'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:addParameter");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "mw.GameScene:addParameter");

            if (!ok) { break; }
            cobj->addParameter(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:addParameter");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "mw.GameScene:addParameter");

            if (!ok) { break; }
            cobj->addParameter(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:addParameter");

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.GameScene:addParameter");

            if (!ok) { break; }
            cobj->addParameter(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:addParameter");

            if (!ok) { break; }
            cocos2d::Ref* arg1;
            ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref",&arg1);

            if (!ok) { break; }
            cobj->addParameter(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "mw.GameScene:addParameter",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_addParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_getRefParameter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getRefParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:getRefParameter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getRefParameter'", nullptr);
            return 0;
        }
        cocos2d::Ref* ret = cobj->getRefParameter(arg0);
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getRefParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getRefParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_getMemoryWarningLine(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getMemoryWarningLine'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getMemoryWarningLine'", nullptr);
            return 0;
        }
        double ret = cobj->getMemoryWarningLine();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getMemoryWarningLine",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getMemoryWarningLine'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_setMemoryWarningLine(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_setMemoryWarningLine'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "mw.GameScene:setMemoryWarningLine");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_setMemoryWarningLine'", nullptr);
            return 0;
        }
        cobj->setMemoryWarningLine(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:setMemoryWarningLine",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_setMemoryWarningLine'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_getStringParameter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getStringParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:getStringParameter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getStringParameter'", nullptr);
            return 0;
        }
        std::string ret = cobj->getStringParameter(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getStringParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getStringParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_unloadViewControllerByIdentifier(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_unloadViewControllerByIdentifier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:unloadViewControllerByIdentifier");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_unloadViewControllerByIdentifier'", nullptr);
            return 0;
        }
        cobj->unloadViewControllerByIdentifier(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:unloadViewControllerByIdentifier",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_unloadViewControllerByIdentifier'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_getNumberParameter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGameScene_getNumberParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GameScene:getNumberParameter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_getNumberParameter'", nullptr);
            return 0;
        }
        double ret = cobj->getNumberParameter(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GameScene:getNumberParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_getNumberParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGameScene_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameScene_create'", nullptr);
            return 0;
        }
        mwframework::MWGameScene* ret = mwframework::MWGameScene::create();
        object_to_luaval<mwframework::MWGameScene>(tolua_S, "mw.GameScene",(mwframework::MWGameScene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GameScene:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameScene_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWGameScene_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWGameScene)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.GameScene",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWGameScene* self = (mwframework::MWGameScene*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWGameScene(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.GameScene");
    tolua_cclass(tolua_S,"GameScene","mw.GameScene","cc.Scene",nullptr);

    tolua_beginmodule(tolua_S,"GameScene");
        tolua_function(tolua_S,"getViewControllers",lua_mwframework_MWGameScene_getViewControllers);
        tolua_function(tolua_S,"unloadViewController",lua_mwframework_MWGameScene_unloadViewController);
        tolua_function(tolua_S,"loadViewController",lua_mwframework_MWGameScene_loadViewController);
        tolua_function(tolua_S,"getViewControllerByIdentifier",lua_mwframework_MWGameScene_getViewControllerByIdentifier);
        tolua_function(tolua_S,"getBooleanParameter",lua_mwframework_MWGameScene_getBooleanParameter);
        tolua_function(tolua_S,"unloadAllViewControllers",lua_mwframework_MWGameScene_unloadAllViewControllers);
        tolua_function(tolua_S,"addParameter",lua_mwframework_MWGameScene_addParameter);
        tolua_function(tolua_S,"getRefParameter",lua_mwframework_MWGameScene_getRefParameter);
        tolua_function(tolua_S,"getMemoryWarningLine",lua_mwframework_MWGameScene_getMemoryWarningLine);
        tolua_function(tolua_S,"setMemoryWarningLine",lua_mwframework_MWGameScene_setMemoryWarningLine);
        tolua_function(tolua_S,"getStringParameter",lua_mwframework_MWGameScene_getStringParameter);
        tolua_function(tolua_S,"unloadViewControllerByIdentifier",lua_mwframework_MWGameScene_unloadViewControllerByIdentifier);
        tolua_function(tolua_S,"getNumberParameter",lua_mwframework_MWGameScene_getNumberParameter);
        tolua_function(tolua_S,"create", lua_mwframework_MWGameScene_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWGameScene).name();
    g_luaType[typeName] = "mw.GameScene";
    g_typeCast["GameScene"] = "mw.GameScene";
    return 1;
}

int lua_mwframework_MWViewController_segue(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWViewController_segue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewController_segue'", nullptr);
            return 0;
        }
        mwframework::MWViewSegue* ret = cobj->segue();
        object_to_luaval<mwframework::MWViewSegue>(tolua_S, "mw.ViewSegue",(mwframework::MWViewSegue*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ViewController:segue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWViewController_segue'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWViewController_scene(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWViewController_scene'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewController_scene'", nullptr);
            return 0;
        }
        mwframework::MWGameScene* ret = cobj->scene();
        object_to_luaval<mwframework::MWGameScene>(tolua_S, "mw.GameScene",(mwframework::MWGameScene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ViewController:scene",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWViewController_scene'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWViewController_getIdentifier(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWViewController_getIdentifier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewController_getIdentifier'", nullptr);
            return 0;
        }
        std::string ret = cobj->getIdentifier();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ViewController:getIdentifier",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWViewController_getIdentifier'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWViewController_view(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWViewController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWViewController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWViewController_view'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewController_view'", nullptr);
            return 0;
        }
        mwframework::MWGameView* ret = cobj->view();
        object_to_luaval<mwframework::MWGameView>(tolua_S, "mw.GameView",(mwframework::MWGameView*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ViewController:view",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWViewController_view'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWViewController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.ViewController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewController_create'", nullptr);
            return 0;
        }
        mwframework::MWViewController* ret = mwframework::MWViewController::create();
        object_to_luaval<mwframework::MWViewController>(tolua_S, "mw.ViewController",(mwframework::MWViewController*)ret);
        return 1;
    }
    if (argc == 1)
    {
        mwframework::MWViewSegue* arg0;
        ok &= luaval_to_object<mwframework::MWViewSegue>(tolua_S, 2, "mw.ViewSegue",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewController_create'", nullptr);
            return 0;
        }
        mwframework::MWViewController* ret = mwframework::MWViewController::create(arg0);
        object_to_luaval<mwframework::MWViewController>(tolua_S, "mw.ViewController",(mwframework::MWViewController*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.ViewController:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWViewController_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWViewController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWViewController)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.ViewController",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWViewController* self = (mwframework::MWViewController*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWViewController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.ViewController");
    tolua_cclass(tolua_S,"ViewController","mw.ViewController","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"ViewController");
        tolua_function(tolua_S,"segue",lua_mwframework_MWViewController_segue);
        tolua_function(tolua_S,"scene",lua_mwframework_MWViewController_scene);
        tolua_function(tolua_S,"getIdentifier",lua_mwframework_MWViewController_getIdentifier);
        tolua_function(tolua_S,"view",lua_mwframework_MWViewController_view);
        tolua_function(tolua_S,"create", lua_mwframework_MWViewController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWViewController).name();
    g_luaType[typeName] = "mw.ViewController";
    g_typeCast["ViewController"] = "mw.ViewController";
    return 1;
}

int lua_mwframework_MWGameView_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GameView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGameView_create'", nullptr);
            return 0;
        }
        mwframework::MWGameView* ret = mwframework::MWGameView::create();
        object_to_luaval<mwframework::MWGameView>(tolua_S, "mw.GameView",(mwframework::MWGameView*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GameView:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGameView_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWGameView_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWGameView)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.GameView",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWGameView* self = (mwframework::MWGameView*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWGameView(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.GameView");
    tolua_cclass(tolua_S,"GameView","mw.GameView","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"GameView");
        tolua_function(tolua_S,"create", lua_mwframework_MWGameView_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWGameView).name();
    g_luaType[typeName] = "mw.GameView";
    g_typeCast["GameView"] = "mw.GameView";
    return 1;
}

int lua_mwframework_MWViewSegue_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.ViewSegue",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWViewSegue_create'", nullptr);
            return 0;
        }
        mwframework::MWViewSegue* ret = mwframework::MWViewSegue::create();
        object_to_luaval<mwframework::MWViewSegue>(tolua_S, "mw.ViewSegue",(mwframework::MWViewSegue*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.ViewSegue:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWViewSegue_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWViewSegue_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWViewSegue)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.ViewSegue",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWViewSegue* self = (mwframework::MWViewSegue*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWViewSegue(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.ViewSegue");
    tolua_cclass(tolua_S,"ViewSegue","mw.ViewSegue","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"ViewSegue");
        tolua_function(tolua_S,"create", lua_mwframework_MWViewSegue_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWViewSegue).name();
    g_luaType[typeName] = "mw.ViewSegue";
    g_typeCast["ViewSegue"] = "mw.ViewSegue";
    return 1;
}

int lua_mwframework_MWSqliteDb_executeNonQuery(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSqliteDb_executeNonQuery'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.SqliteDb:executeNonQuery");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSqliteDb_executeNonQuery'", nullptr);
            return 0;
        }
        bool ret = cobj->executeNonQuery(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SqliteDb:executeNonQuery",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSqliteDb_executeNonQuery'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSqliteDb_endTransaction(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSqliteDb_endTransaction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "mw.SqliteDb:endTransaction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSqliteDb_endTransaction'", nullptr);
            return 0;
        }
        bool ret = cobj->endTransaction(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SqliteDb:endTransaction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSqliteDb_endTransaction'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSqliteDb_beginTransaction(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSqliteDb* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSqliteDb*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSqliteDb_beginTransaction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSqliteDb_beginTransaction'", nullptr);
            return 0;
        }
        bool ret = cobj->beginTransaction();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SqliteDb:beginTransaction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSqliteDb_beginTransaction'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSqliteDb_openDb(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.SqliteDb:openDb");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSqliteDb_openDb'", nullptr);
            return 0;
        }
        mwframework::MWSqliteDb* ret = mwframework::MWSqliteDb::openDb(arg0);
        object_to_luaval<mwframework::MWSqliteDb>(tolua_S, "mw.SqliteDb",(mwframework::MWSqliteDb*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.SqliteDb:openDb",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSqliteDb_openDb'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWSqliteDb_clearConnectionCache(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.SqliteDb",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSqliteDb_clearConnectionCache'", nullptr);
            return 0;
        }
        mwframework::MWSqliteDb::clearConnectionCache();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.SqliteDb:clearConnectionCache",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSqliteDb_clearConnectionCache'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWSqliteDb_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWSqliteDb)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.SqliteDb",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWSqliteDb* self = (mwframework::MWSqliteDb*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWSqliteDb(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.SqliteDb");
    tolua_cclass(tolua_S,"SqliteDb","mw.SqliteDb","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"SqliteDb");
        tolua_function(tolua_S,"executeNonQuery",lua_mwframework_MWSqliteDb_executeNonQuery);
        tolua_function(tolua_S,"endTransaction",lua_mwframework_MWSqliteDb_endTransaction);
        tolua_function(tolua_S,"beginTransaction",lua_mwframework_MWSqliteDb_beginTransaction);
        tolua_function(tolua_S,"openDb", lua_mwframework_MWSqliteDb_openDb);
        tolua_function(tolua_S,"clearConnectionCache", lua_mwframework_MWSqliteDb_clearConnectionCache);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWSqliteDb).name();
    g_luaType[typeName] = "mw.SqliteDb";
    g_typeCast["SqliteDb"] = "mw.SqliteDb";
    return 1;
}

int lua_mwframework_MWZipData_getCompressedFileData(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWZipData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWZipData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWZipData_getCompressedFileData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:getCompressedFileData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_getCompressedFileData'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->getCompressedFileData(arg0);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:getCompressedFileData");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.ZipData:getCompressedFileData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_getCompressedFileData'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->getCompressedFileData(arg0, arg1);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ZipData:getCompressedFileData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_getCompressedFileData'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWZipData_zipNewFile(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWZipData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWZipData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWZipData_zipNewFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        mwframework::MWBinaryData* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:zipNewFile");

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 3, "mw.BinaryData",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_zipNewFile'", nullptr);
            return 0;
        }
        bool ret = cobj->zipNewFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        mwframework::MWBinaryData* arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:zipNewFile");

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 3, "mw.BinaryData",&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "mw.ZipData:zipNewFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_zipNewFile'", nullptr);
            return 0;
        }
        bool ret = cobj->zipNewFile(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4) 
    {
        std::string arg0;
        mwframework::MWBinaryData* arg1;
        std::string arg2;
        int arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:zipNewFile");

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 3, "mw.BinaryData",&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "mw.ZipData:zipNewFile");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "mw.ZipData:zipNewFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_zipNewFile'", nullptr);
            return 0;
        }
        bool ret = cobj->zipNewFile(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ZipData:zipNewFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_zipNewFile'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWZipData_beginUnzip(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWZipData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWZipData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWZipData_beginUnzip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_beginUnzip'", nullptr);
            return 0;
        }
        cobj->beginUnzip();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ZipData:beginUnzip",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_beginUnzip'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWZipData_endUnzip(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWZipData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWZipData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWZipData_endUnzip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_endUnzip'", nullptr);
            return 0;
        }
        cobj->endUnzip();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ZipData:endUnzip",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_endUnzip'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWZipData_beginZip(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWZipData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWZipData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWZipData_beginZip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_beginZip'", nullptr);
            return 0;
        }
        cobj->beginZip();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ZipData:beginZip",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_beginZip'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWZipData_endZip(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWZipData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWZipData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWZipData_endZip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_endZip'", nullptr);
            return 0;
        }
        cobj->endZip();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.ZipData:endZip",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_endZip'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWZipData_createWithExistingFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:createWithExistingFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_createWithExistingFile'", nullptr);
            return 0;
        }
        mwframework::MWZipData* ret = mwframework::MWZipData::createWithExistingFile(arg0);
        object_to_luaval<mwframework::MWZipData>(tolua_S, "mw.ZipData",(mwframework::MWZipData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.ZipData:createWithExistingFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_createWithExistingFile'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWZipData_createWithNewFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.ZipData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.ZipData:createWithNewFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWZipData_createWithNewFile'", nullptr);
            return 0;
        }
        mwframework::MWZipData* ret = mwframework::MWZipData::createWithNewFile(arg0);
        object_to_luaval<mwframework::MWZipData>(tolua_S, "mw.ZipData",(mwframework::MWZipData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.ZipData:createWithNewFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWZipData_createWithNewFile'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWZipData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWZipData)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.ZipData",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWZipData* self = (mwframework::MWZipData*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWZipData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.ZipData");
    tolua_cclass(tolua_S,"ZipData","mw.ZipData","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"ZipData");
        tolua_function(tolua_S,"getCompressedFileData",lua_mwframework_MWZipData_getCompressedFileData);
        tolua_function(tolua_S,"zipNewFile",lua_mwframework_MWZipData_zipNewFile);
        tolua_function(tolua_S,"beginUnzip",lua_mwframework_MWZipData_beginUnzip);
        tolua_function(tolua_S,"endUnzip",lua_mwframework_MWZipData_endUnzip);
        tolua_function(tolua_S,"beginZip",lua_mwframework_MWZipData_beginZip);
        tolua_function(tolua_S,"endZip",lua_mwframework_MWZipData_endZip);
        tolua_function(tolua_S,"createWithExistingFile", lua_mwframework_MWZipData_createWithExistingFile);
        tolua_function(tolua_S,"createWithNewFile", lua_mwframework_MWZipData_createWithNewFile);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWZipData).name();
    g_luaType[typeName] = "mw.ZipData";
    g_typeCast["ZipData"] = "mw.ZipData";
    return 1;
}

int lua_mwframework_MWGifFrame_setSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFrame_setSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SpriteFrame* arg0;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFrame_setSpriteFrame'", nullptr);
            return 0;
        }
        cobj->setSpriteFrame(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFrame:setSpriteFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFrame_setSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFrame_setDuration(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFrame_setDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.GifFrame:setDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFrame_setDuration'", nullptr);
            return 0;
        }
        cobj->setDuration(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFrame:setDuration",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFrame_setDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFrame_getSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFrame_getSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFrame_getSpriteFrame'", nullptr);
            return 0;
        }
        cocos2d::SpriteFrame* ret = cobj->getSpriteFrame();
        object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFrame:getSpriteFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFrame_getSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFrame_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFrame_getDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFrame_getDuration'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getDuration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFrame:getDuration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFrame_getDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GifFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::SpriteFrame* arg0;
        unsigned int arg1;
        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.GifFrame:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFrame_create'", nullptr);
            return 0;
        }
        mwframework::MWGifFrame* ret = mwframework::MWGifFrame::create(arg0, arg1);
        object_to_luaval<mwframework::MWGifFrame>(tolua_S, "mw.GifFrame",(mwframework::MWGifFrame*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GifFrame:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFrame_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWGifFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWGifFrame)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.GifFrame",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWGifFrame* self = (mwframework::MWGifFrame*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWGifFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.GifFrame");
    tolua_cclass(tolua_S,"GifFrame","mw.GifFrame","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"GifFrame");
        tolua_function(tolua_S,"setSpriteFrame",lua_mwframework_MWGifFrame_setSpriteFrame);
        tolua_function(tolua_S,"setDuration",lua_mwframework_MWGifFrame_setDuration);
        tolua_function(tolua_S,"getSpriteFrame",lua_mwframework_MWGifFrame_getSpriteFrame);
        tolua_function(tolua_S,"getDuration",lua_mwframework_MWGifFrame_getDuration);
        tolua_function(tolua_S,"create", lua_mwframework_MWGifFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWGifFrame).name();
    g_luaType[typeName] = "mw.GifFrame";
    g_typeCast["GifFrame"] = "mw.GifFrame";
    return 1;
}

int lua_mwframework_MWGifSprite_play(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_play'", nullptr);
            return 0;
        }
        cobj->play();
        return 0;
    }
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.GifSprite:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_play'", nullptr);
            return 0;
        }
        cobj->play(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:play",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_play'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_pause(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_pause'", nullptr);
            return 0;
        }
        cobj->pause();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_setSpeedRatio(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_setSpeedRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "mw.GifSprite:setSpeedRatio");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_setSpeedRatio'", nullptr);
            return 0;
        }
        cobj->setSpeedRatio(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:setSpeedRatio",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_setSpeedRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_getSpriteFrameAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_getSpriteFrameAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "mw.GifSprite:getSpriteFrameAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_getSpriteFrameAtIndex'", nullptr);
            return 0;
        }
        cocos2d::SpriteFrame* ret = cobj->getSpriteFrameAtIndex(arg0);
        object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:getSpriteFrameAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_getSpriteFrameAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_resume(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_resume'", nullptr);
            return 0;
        }
        cobj->resume();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:resume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_resume'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_getSpeedRatio(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_getSpeedRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_getSpeedRatio'", nullptr);
            return 0;
        }
        double ret = cobj->getSpeedRatio();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:getSpeedRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_getSpeedRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_stop(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifSprite_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifSprite:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifSprite_createWithFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GifSprite:createWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_createWithFile'", nullptr);
            return 0;
        }
        mwframework::MWGifSprite* ret = mwframework::MWGifSprite::createWithFile(arg0);
        object_to_luaval<mwframework::MWGifSprite>(tolua_S, "mw.GifSprite",(mwframework::MWGifSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GifSprite:createWithFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_createWithFile'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWGifSprite_createWithFrames(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        mwframework::MWArrayList* arg0;
        ok &= luaval_to_object<mwframework::MWArrayList>(tolua_S, 2, "mw.ArrayList",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_createWithFrames'", nullptr);
            return 0;
        }
        mwframework::MWGifSprite* ret = mwframework::MWGifSprite::createWithFrames(arg0);
        object_to_luaval<mwframework::MWGifSprite>(tolua_S, "mw.GifSprite",(mwframework::MWGifSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GifSprite:createWithFrames",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_createWithFrames'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWGifSprite_createWithRawData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GifSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        mwframework::MWBinaryData* arg0;
        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifSprite_createWithRawData'", nullptr);
            return 0;
        }
        mwframework::MWGifSprite* ret = mwframework::MWGifSprite::createWithRawData(arg0);
        object_to_luaval<mwframework::MWGifSprite>(tolua_S, "mw.GifSprite",(mwframework::MWGifSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GifSprite:createWithRawData",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifSprite_createWithRawData'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWGifSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWGifSprite)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.GifSprite",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWGifSprite* self = (mwframework::MWGifSprite*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWGifSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.GifSprite");
    tolua_cclass(tolua_S,"GifSprite","mw.GifSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"GifSprite");
        tolua_function(tolua_S,"play",lua_mwframework_MWGifSprite_play);
        tolua_function(tolua_S,"pause",lua_mwframework_MWGifSprite_pause);
        tolua_function(tolua_S,"setSpeedRatio",lua_mwframework_MWGifSprite_setSpeedRatio);
        tolua_function(tolua_S,"getSpriteFrameAtIndex",lua_mwframework_MWGifSprite_getSpriteFrameAtIndex);
        tolua_function(tolua_S,"resume",lua_mwframework_MWGifSprite_resume);
        tolua_function(tolua_S,"getSpeedRatio",lua_mwframework_MWGifSprite_getSpeedRatio);
        tolua_function(tolua_S,"stop",lua_mwframework_MWGifSprite_stop);
        tolua_function(tolua_S,"createWithFile", lua_mwframework_MWGifSprite_createWithFile);
        tolua_function(tolua_S,"createWithFrames", lua_mwframework_MWGifSprite_createWithFrames);
        tolua_function(tolua_S,"createWithRawData", lua_mwframework_MWGifSprite_createWithRawData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWGifSprite).name();
    g_luaType[typeName] = "mw.GifSprite";
    g_typeCast["GifSprite"] = "mw.GifSprite";
    return 1;
}

int lua_mwframework_MWGifFramesCache_removeAll(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFramesCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFramesCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFramesCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFramesCache_removeAll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFramesCache_removeAll'", nullptr);
            return 0;
        }
        cobj->removeAll();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFramesCache:removeAll",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFramesCache_removeAll'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFramesCache_addGifFramesCache(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFramesCache* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFramesCache",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (mwframework::MWGifFramesCache*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFramesCache_addGifFramesCache'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            mwframework::MWBinaryData* arg0;
            ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.GifFramesCache:addGifFramesCache");

            if (!ok) { break; }
            cobj->addGifFramesCache(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GifFramesCache:addGifFramesCache");

            if (!ok) { break; }
            cobj->addGifFramesCache(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            mwframework::MWGifSprite* arg0;
            ok &= luaval_to_object<mwframework::MWGifSprite>(tolua_S, 2, "mw.GifSprite",&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.GifFramesCache:addGifFramesCache");

            if (!ok) { break; }
            cobj->addGifFramesCache(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            mwframework::MWArrayList* arg0;
            ok &= luaval_to_object<mwframework::MWArrayList>(tolua_S, 2, "mw.ArrayList",&arg0);

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.GifFramesCache:addGifFramesCache");

            if (!ok) { break; }
            cobj->addGifFramesCache(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "mw.GifFramesCache:addGifFramesCache",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFramesCache_addGifFramesCache'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFramesCache_getGifSprite(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFramesCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFramesCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFramesCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFramesCache_getGifSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GifFramesCache:getGifSprite");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFramesCache_getGifSprite'", nullptr);
            return 0;
        }
        mwframework::MWGifSprite* ret = cobj->getGifSprite(arg0);
        object_to_luaval<mwframework::MWGifSprite>(tolua_S, "mw.GifSprite",(mwframework::MWGifSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFramesCache:getGifSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFramesCache_getGifSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFramesCache_removeGifFramesCache(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWGifFramesCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.GifFramesCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWGifFramesCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWGifFramesCache_removeGifFramesCache'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.GifFramesCache:removeGifFramesCache");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFramesCache_removeGifFramesCache'", nullptr);
            return 0;
        }
        cobj->removeGifFramesCache(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.GifFramesCache:removeGifFramesCache",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFramesCache_removeGifFramesCache'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWGifFramesCache_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.GifFramesCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWGifFramesCache_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWGifFramesCache* ret = mwframework::MWGifFramesCache::getInstance();
        object_to_luaval<mwframework::MWGifFramesCache>(tolua_S, "mw.GifFramesCache",(mwframework::MWGifFramesCache*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.GifFramesCache:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWGifFramesCache_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWGifFramesCache_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWGifFramesCache)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.GifFramesCache",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWGifFramesCache* self = (mwframework::MWGifFramesCache*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWGifFramesCache(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.GifFramesCache");
    tolua_cclass(tolua_S,"GifFramesCache","mw.GifFramesCache","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"GifFramesCache");
        tolua_function(tolua_S,"removeAll",lua_mwframework_MWGifFramesCache_removeAll);
        tolua_function(tolua_S,"addGifFramesCache",lua_mwframework_MWGifFramesCache_addGifFramesCache);
        tolua_function(tolua_S,"getGifSprite",lua_mwframework_MWGifFramesCache_getGifSprite);
        tolua_function(tolua_S,"removeGifFramesCache",lua_mwframework_MWGifFramesCache_removeGifFramesCache);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWGifFramesCache_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWGifFramesCache).name();
    g_luaType[typeName] = "mw.GifFramesCache";
    g_typeCast["GifFramesCache"] = "mw.GifFramesCache";
    return 1;
}

int lua_mwframework_MWSvgSprite_setVectorScale(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSvgSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SvgSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSvgSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSvgSprite_setVectorScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "mw.SvgSprite:setVectorScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSvgSprite_setVectorScale'", nullptr);
            return 0;
        }
        cobj->setVectorScale(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SvgSprite:setVectorScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSvgSprite_setVectorScale'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSvgSprite_getVectorScale(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWSvgSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.SvgSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWSvgSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWSvgSprite_getVectorScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSvgSprite_getVectorScale'", nullptr);
            return 0;
        }
        double ret = cobj->getVectorScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.SvgSprite:getVectorScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSvgSprite_getVectorScale'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWSvgSprite_createWithFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.SvgSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.SvgSprite:createWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSvgSprite_createWithFile'", nullptr);
            return 0;
        }
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithFile(arg0);
        object_to_luaval<mwframework::MWSvgSprite>(tolua_S, "mw.SvgSprite",(mwframework::MWSvgSprite*)ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        double arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.SvgSprite:createWithFile");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "mw.SvgSprite:createWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSvgSprite_createWithFile'", nullptr);
            return 0;
        }
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithFile(arg0, arg1);
        object_to_luaval<mwframework::MWSvgSprite>(tolua_S, "mw.SvgSprite",(mwframework::MWSvgSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.SvgSprite:createWithFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSvgSprite_createWithFile'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWSvgSprite_createWithRawData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.SvgSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        mwframework::MWBinaryData* arg0;
        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSvgSprite_createWithRawData'", nullptr);
            return 0;
        }
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithRawData(arg0);
        object_to_luaval<mwframework::MWSvgSprite>(tolua_S, "mw.SvgSprite",(mwframework::MWSvgSprite*)ret);
        return 1;
    }
    if (argc == 2)
    {
        mwframework::MWBinaryData* arg0;
        double arg1;
        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);
        ok &= luaval_to_number(tolua_S, 3,&arg1, "mw.SvgSprite:createWithRawData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWSvgSprite_createWithRawData'", nullptr);
            return 0;
        }
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithRawData(arg0, arg1);
        object_to_luaval<mwframework::MWSvgSprite>(tolua_S, "mw.SvgSprite",(mwframework::MWSvgSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.SvgSprite:createWithRawData",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWSvgSprite_createWithRawData'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWSvgSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWSvgSprite)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.SvgSprite",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWSvgSprite* self = (mwframework::MWSvgSprite*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWSvgSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.SvgSprite");
    tolua_cclass(tolua_S,"SvgSprite","mw.SvgSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"SvgSprite");
        tolua_function(tolua_S,"setVectorScale",lua_mwframework_MWSvgSprite_setVectorScale);
        tolua_function(tolua_S,"getVectorScale",lua_mwframework_MWSvgSprite_getVectorScale);
        tolua_function(tolua_S,"createWithFile", lua_mwframework_MWSvgSprite_createWithFile);
        tolua_function(tolua_S,"createWithRawData", lua_mwframework_MWSvgSprite_createWithRawData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWSvgSprite).name();
    g_luaType[typeName] = "mw.SvgSprite";
    g_typeCast["SvgSprite"] = "mw.SvgSprite";
    return 1;
}

int lua_mwframework_MWJsonObject_count(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_count'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_count'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->count();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:count",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_count'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_getJsonArray(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_getJsonArray'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:getJsonArray");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_getJsonArray'", nullptr);
            return 0;
        }
        mwframework::MWJsonArray* ret = cobj->getJsonArray(arg0);
        object_to_luaval<mwframework::MWJsonArray>(tolua_S, "mw.JsonArray",(mwframework::MWJsonArray*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:getJsonArray",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_getJsonArray'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_getBoolean(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_getBoolean'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:getBoolean");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_getBoolean'", nullptr);
            return 0;
        }
        bool ret = cobj->getBoolean(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:getBoolean",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_getBoolean'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_putBoolean(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_putBoolean'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:putBoolean");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "mw.JsonObject:putBoolean");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_putBoolean'", nullptr);
            return 0;
        }
        cobj->putBoolean(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:putBoolean",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_putBoolean'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_getString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_getString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:getString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_getString'", nullptr);
            return 0;
        }
        const char* ret = cobj->getString(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:getString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_getString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_getNumber(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_getNumber'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:getNumber");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_getNumber'", nullptr);
            return 0;
        }
        double ret = cobj->getNumber(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:getNumber",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_getNumber'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_putJsonArray(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_putJsonArray'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        mwframework::MWJsonArray* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:putJsonArray");

        ok &= luaval_to_object<mwframework::MWJsonArray>(tolua_S, 3, "mw.JsonArray",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_putJsonArray'", nullptr);
            return 0;
        }
        cobj->putJsonArray(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:putJsonArray",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_putJsonArray'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_putJsonObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_putJsonObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        mwframework::MWJsonObject* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:putJsonObject");

        ok &= luaval_to_object<mwframework::MWJsonObject>(tolua_S, 3, "mw.JsonObject",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_putJsonObject'", nullptr);
            return 0;
        }
        cobj->putJsonObject(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:putJsonObject",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_putJsonObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_clear(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_toLuaString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_toLuaString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_toLuaString'", nullptr);
            return 0;
        }
        std::string ret = cobj->toLuaString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:toLuaString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_toLuaString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_putNumber(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_putNumber'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:putNumber");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "mw.JsonObject:putNumber");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_putNumber'", nullptr);
            return 0;
        }
        cobj->putNumber(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:putNumber",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_putNumber'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_remove(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_remove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:remove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_remove'", nullptr);
            return 0;
        }
        cobj->remove(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:remove",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_remove'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_putString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_putString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:putString");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.JsonObject:putString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_putString'", nullptr);
            return 0;
        }
        cobj->putString(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:putString",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_putString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_getJsonObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_getJsonObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:getJsonObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_getJsonObject'", nullptr);
            return 0;
        }
        mwframework::MWJsonObject* ret = cobj->getJsonObject(arg0);
        object_to_luaval<mwframework::MWJsonObject>(tolua_S, "mw.JsonObject",(mwframework::MWJsonObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:getJsonObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_getJsonObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_toPrettyString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_toPrettyString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_toPrettyString'", nullptr);
            return 0;
        }
        std::string ret = cobj->toPrettyString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:toPrettyString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_toPrettyString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_hasKey(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_hasKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:hasKey");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_hasKey'", nullptr);
            return 0;
        }
        bool ret = cobj->hasKey(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:hasKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_hasKey'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_getObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonObject_getObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:getObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_getObject'", nullptr);
            return 0;
        }
        mwframework::MWObject* ret = cobj->getObject(arg0);
        object_to_luaval<mwframework::MWObject>(tolua_S, "mw.Object",(mwframework::MWObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonObject:getObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_getObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonObject_createWithFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:createWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_createWithFile'", nullptr);
            return 0;
        }
        mwframework::MWJsonObject* ret = mwframework::MWJsonObject::createWithFile(arg0);
        object_to_luaval<mwframework::MWJsonObject>(tolua_S, "mw.JsonObject",(mwframework::MWJsonObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.JsonObject:createWithFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_createWithFile'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWJsonObject_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_create'", nullptr);
            return 0;
        }
        mwframework::MWJsonObject* ret = mwframework::MWJsonObject::create();
        object_to_luaval<mwframework::MWJsonObject>(tolua_S, "mw.JsonObject",(mwframework::MWJsonObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.JsonObject:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWJsonObject_createWithString(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.JsonObject",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonObject:createWithString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonObject_createWithString'", nullptr);
            return 0;
        }
        mwframework::MWJsonObject* ret = mwframework::MWJsonObject::createWithString(arg0);
        object_to_luaval<mwframework::MWJsonObject>(tolua_S, "mw.JsonObject",(mwframework::MWJsonObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.JsonObject:createWithString",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonObject_createWithString'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWJsonObject_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWJsonObject)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.JsonObject",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWJsonObject* self = (mwframework::MWJsonObject*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWJsonObject(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.JsonObject");
    tolua_cclass(tolua_S,"JsonObject","mw.JsonObject","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"JsonObject");
        tolua_function(tolua_S,"count",lua_mwframework_MWJsonObject_count);
        tolua_function(tolua_S,"getJsonArray",lua_mwframework_MWJsonObject_getJsonArray);
        tolua_function(tolua_S,"getBoolean",lua_mwframework_MWJsonObject_getBoolean);
        tolua_function(tolua_S,"putBoolean",lua_mwframework_MWJsonObject_putBoolean);
        tolua_function(tolua_S,"getString",lua_mwframework_MWJsonObject_getString);
        tolua_function(tolua_S,"getNumber",lua_mwframework_MWJsonObject_getNumber);
        tolua_function(tolua_S,"putJsonArray",lua_mwframework_MWJsonObject_putJsonArray);
        tolua_function(tolua_S,"putJsonObject",lua_mwframework_MWJsonObject_putJsonObject);
        tolua_function(tolua_S,"clear",lua_mwframework_MWJsonObject_clear);
        tolua_function(tolua_S,"toLuaString",lua_mwframework_MWJsonObject_toLuaString);
        tolua_function(tolua_S,"putNumber",lua_mwframework_MWJsonObject_putNumber);
        tolua_function(tolua_S,"remove",lua_mwframework_MWJsonObject_remove);
        tolua_function(tolua_S,"putString",lua_mwframework_MWJsonObject_putString);
        tolua_function(tolua_S,"getJsonObject",lua_mwframework_MWJsonObject_getJsonObject);
        tolua_function(tolua_S,"toPrettyString",lua_mwframework_MWJsonObject_toPrettyString);
        tolua_function(tolua_S,"hasKey",lua_mwframework_MWJsonObject_hasKey);
        tolua_function(tolua_S,"getObject",lua_mwframework_MWJsonObject_getObject);
        tolua_function(tolua_S,"createWithFile", lua_mwframework_MWJsonObject_createWithFile);
        tolua_function(tolua_S,"create", lua_mwframework_MWJsonObject_create);
        tolua_function(tolua_S,"createWithString", lua_mwframework_MWJsonObject_createWithString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWJsonObject).name();
    g_luaType[typeName] = "mw.JsonObject";
    g_typeCast["JsonObject"] = "mw.JsonObject";
    return 1;
}

int lua_mwframework_MWJsonArray_count(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_count'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_count'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->count();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:count",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_count'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_getObjectAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_getObjectAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.JsonArray:getObjectAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_getObjectAt'", nullptr);
            return 0;
        }
        mwframework::MWObject* ret = cobj->getObjectAt(arg0);
        object_to_luaval<mwframework::MWObject>(tolua_S, "mw.Object",(mwframework::MWObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:getObjectAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_getObjectAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_toPrettyString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_toPrettyString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_toPrettyString'", nullptr);
            return 0;
        }
        std::string ret = cobj->toPrettyString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:toPrettyString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_toPrettyString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_getStringAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_getStringAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.JsonArray:getStringAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_getStringAt'", nullptr);
            return 0;
        }
        const char* ret = cobj->getStringAt(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:getStringAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_getStringAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_insertJsonArray(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_insertJsonArray'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWJsonArray* arg0;
        unsigned int arg1;

        ok &= luaval_to_object<mwframework::MWJsonArray>(tolua_S, 2, "mw.JsonArray",&arg0);

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.JsonArray:insertJsonArray");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_insertJsonArray'", nullptr);
            return 0;
        }
        cobj->insertJsonArray(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:insertJsonArray",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_insertJsonArray'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_appendJsonArray(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_appendJsonArray'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWJsonArray* arg0;

        ok &= luaval_to_object<mwframework::MWJsonArray>(tolua_S, 2, "mw.JsonArray",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_appendJsonArray'", nullptr);
            return 0;
        }
        cobj->appendJsonArray(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:appendJsonArray",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_appendJsonArray'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_insertJsonObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_insertJsonObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWJsonObject* arg0;
        unsigned int arg1;

        ok &= luaval_to_object<mwframework::MWJsonObject>(tolua_S, 2, "mw.JsonObject",&arg0);

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.JsonArray:insertJsonObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_insertJsonObject'", nullptr);
            return 0;
        }
        cobj->insertJsonObject(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:insertJsonObject",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_insertJsonObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_clear(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_appendJsonObject(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_appendJsonObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWJsonObject* arg0;

        ok &= luaval_to_object<mwframework::MWJsonObject>(tolua_S, 2, "mw.JsonObject",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_appendJsonObject'", nullptr);
            return 0;
        }
        cobj->appendJsonObject(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:appendJsonObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_appendJsonObject'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_insertNumber(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_insertNumber'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        unsigned int arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "mw.JsonArray:insertNumber");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.JsonArray:insertNumber");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_insertNumber'", nullptr);
            return 0;
        }
        cobj->insertNumber(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:insertNumber",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_insertNumber'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_removeAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_removeAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.JsonArray:removeAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_removeAt'", nullptr);
            return 0;
        }
        cobj->removeAt(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:removeAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_removeAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_appendNumber(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_appendNumber'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "mw.JsonArray:appendNumber");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_appendNumber'", nullptr);
            return 0;
        }
        cobj->appendNumber(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:appendNumber",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_appendNumber'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_appendBoolean(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_appendBoolean'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "mw.JsonArray:appendBoolean");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_appendBoolean'", nullptr);
            return 0;
        }
        cobj->appendBoolean(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:appendBoolean",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_appendBoolean'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_toLuaString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_toLuaString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_toLuaString'", nullptr);
            return 0;
        }
        std::string ret = cobj->toLuaString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:toLuaString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_toLuaString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_getBooleanAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_getBooleanAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "mw.JsonArray:getBooleanAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_getBooleanAt'", nullptr);
            return 0;
        }
        bool ret = cobj->getBooleanAt(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:getBooleanAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_getBooleanAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_insertString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_insertString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonArray:insertString");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "mw.JsonArray:insertString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_insertString'", nullptr);
            return 0;
        }
        cobj->insertString(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:insertString",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_insertString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_getJsonArrayAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_getJsonArrayAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.JsonArray:getJsonArrayAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_getJsonArrayAt'", nullptr);
            return 0;
        }
        mwframework::MWJsonArray* ret = cobj->getJsonArrayAt(arg0);
        object_to_luaval<mwframework::MWJsonArray>(tolua_S, "mw.JsonArray",(mwframework::MWJsonArray*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:getJsonArrayAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_getJsonArrayAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_appendString(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_appendString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonArray:appendString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_appendString'", nullptr);
            return 0;
        }
        cobj->appendString(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:appendString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_appendString'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_insertBoolean(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_insertBoolean'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        bool arg0;
        unsigned int arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "mw.JsonArray:insertBoolean");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "mw.JsonArray:insertBoolean");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_insertBoolean'", nullptr);
            return 0;
        }
        cobj->insertBoolean(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:insertBoolean",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_insertBoolean'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_getNumberAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_getNumberAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.JsonArray:getNumberAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_getNumberAt'", nullptr);
            return 0;
        }
        double ret = cobj->getNumberAt(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:getNumberAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_getNumberAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_getJsonObjectAt(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWJsonArray* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWJsonArray*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWJsonArray_getJsonObjectAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "mw.JsonArray:getJsonObjectAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_getJsonObjectAt'", nullptr);
            return 0;
        }
        mwframework::MWJsonObject* ret = cobj->getJsonObjectAt(arg0);
        object_to_luaval<mwframework::MWJsonObject>(tolua_S, "mw.JsonObject",(mwframework::MWJsonObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.JsonArray:getJsonObjectAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_getJsonObjectAt'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWJsonArray_createWithFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonArray:createWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_createWithFile'", nullptr);
            return 0;
        }
        mwframework::MWJsonArray* ret = mwframework::MWJsonArray::createWithFile(arg0);
        object_to_luaval<mwframework::MWJsonArray>(tolua_S, "mw.JsonArray",(mwframework::MWJsonArray*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.JsonArray:createWithFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_createWithFile'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWJsonArray_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_create'", nullptr);
            return 0;
        }
        mwframework::MWJsonArray* ret = mwframework::MWJsonArray::create();
        object_to_luaval<mwframework::MWJsonArray>(tolua_S, "mw.JsonArray",(mwframework::MWJsonArray*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.JsonArray:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_create'.",&tolua_err);
#endif
    return 0;
}
int lua_mwframework_MWJsonArray_createWithString(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.JsonArray",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.JsonArray:createWithString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWJsonArray_createWithString'", nullptr);
            return 0;
        }
        mwframework::MWJsonArray* ret = mwframework::MWJsonArray::createWithString(arg0);
        object_to_luaval<mwframework::MWJsonArray>(tolua_S, "mw.JsonArray",(mwframework::MWJsonArray*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.JsonArray:createWithString",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWJsonArray_createWithString'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWJsonArray_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWJsonArray)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.JsonArray",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWJsonArray* self = (mwframework::MWJsonArray*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWJsonArray(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.JsonArray");
    tolua_cclass(tolua_S,"JsonArray","mw.JsonArray","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"JsonArray");
        tolua_function(tolua_S,"count",lua_mwframework_MWJsonArray_count);
        tolua_function(tolua_S,"getObjectAt",lua_mwframework_MWJsonArray_getObjectAt);
        tolua_function(tolua_S,"toPrettyString",lua_mwframework_MWJsonArray_toPrettyString);
        tolua_function(tolua_S,"getStringAt",lua_mwframework_MWJsonArray_getStringAt);
        tolua_function(tolua_S,"insertJsonArray",lua_mwframework_MWJsonArray_insertJsonArray);
        tolua_function(tolua_S,"appendJsonArray",lua_mwframework_MWJsonArray_appendJsonArray);
        tolua_function(tolua_S,"insertJsonObject",lua_mwframework_MWJsonArray_insertJsonObject);
        tolua_function(tolua_S,"clear",lua_mwframework_MWJsonArray_clear);
        tolua_function(tolua_S,"appendJsonObject",lua_mwframework_MWJsonArray_appendJsonObject);
        tolua_function(tolua_S,"insertNumber",lua_mwframework_MWJsonArray_insertNumber);
        tolua_function(tolua_S,"removeAt",lua_mwframework_MWJsonArray_removeAt);
        tolua_function(tolua_S,"appendNumber",lua_mwframework_MWJsonArray_appendNumber);
        tolua_function(tolua_S,"appendBoolean",lua_mwframework_MWJsonArray_appendBoolean);
        tolua_function(tolua_S,"toLuaString",lua_mwframework_MWJsonArray_toLuaString);
        tolua_function(tolua_S,"getBooleanAt",lua_mwframework_MWJsonArray_getBooleanAt);
        tolua_function(tolua_S,"insertString",lua_mwframework_MWJsonArray_insertString);
        tolua_function(tolua_S,"getJsonArrayAt",lua_mwframework_MWJsonArray_getJsonArrayAt);
        tolua_function(tolua_S,"appendString",lua_mwframework_MWJsonArray_appendString);
        tolua_function(tolua_S,"insertBoolean",lua_mwframework_MWJsonArray_insertBoolean);
        tolua_function(tolua_S,"getNumberAt",lua_mwframework_MWJsonArray_getNumberAt);
        tolua_function(tolua_S,"getJsonObjectAt",lua_mwframework_MWJsonArray_getJsonObjectAt);
        tolua_function(tolua_S,"createWithFile", lua_mwframework_MWJsonArray_createWithFile);
        tolua_function(tolua_S,"create", lua_mwframework_MWJsonArray_create);
        tolua_function(tolua_S,"createWithString", lua_mwframework_MWJsonArray_createWithString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWJsonArray).name();
    g_luaType[typeName] = "mw.JsonArray";
    g_typeCast["JsonArray"] = "mw.JsonArray";
    return 1;
}

int lua_mwframework_MWCrypto_encipherAes256(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_encipherAes256'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWBinaryData* arg0;
        std::string arg1;

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.Crypto:encipherAes256");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_encipherAes256'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->encipherAes256(arg0, arg1);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:encipherAes256",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_encipherAes256'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_decodeBase64(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_decodeBase64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Crypto:decodeBase64");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_decodeBase64'", nullptr);
            return 0;
        }
        std::string ret = cobj->decodeBase64(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:decodeBase64",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_decodeBase64'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_decipherXxtea(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_decipherXxtea'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWBinaryData* arg0;
        std::string arg1;

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.Crypto:decipherXxtea");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_decipherXxtea'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->decipherXxtea(arg0, arg1);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:decipherXxtea",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_decipherXxtea'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_md5String(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_md5String'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Crypto:md5String");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_md5String'", nullptr);
            return 0;
        }
        std::string ret = cobj->md5String(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:md5String",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_md5String'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_md5File(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_md5File'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Crypto:md5File");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_md5File'", nullptr);
            return 0;
        }
        std::string ret = cobj->md5File(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:md5File",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_md5File'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_encipherXxtea(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_encipherXxtea'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWBinaryData* arg0;
        std::string arg1;

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.Crypto:encipherXxtea");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_encipherXxtea'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->encipherXxtea(arg0, arg1);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:encipherXxtea",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_encipherXxtea'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_getAes256KeyLength(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_getAes256KeyLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_getAes256KeyLength'", nullptr);
            return 0;
        }
        int ret = cobj->getAes256KeyLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:getAes256KeyLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_getAes256KeyLength'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_decipherAes256(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_decipherAes256'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        mwframework::MWBinaryData* arg0;
        std::string arg1;

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.Crypto:decipherAes256");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_decipherAes256'", nullptr);
            return 0;
        }
        mwframework::MWBinaryData* ret = cobj->decipherAes256(arg0, arg1);
        object_to_luaval<mwframework::MWBinaryData>(tolua_S, "mw.BinaryData",(mwframework::MWBinaryData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:decipherAes256",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_decipherAes256'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_encodeBase64(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_encodeBase64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.Crypto:encodeBase64");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_encodeBase64'", nullptr);
            return 0;
        }
        std::string ret = cobj->encodeBase64(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:encodeBase64",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_encodeBase64'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_md5(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWCrypto* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWCrypto*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWCrypto_md5'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWBinaryData* arg0;

        ok &= luaval_to_object<mwframework::MWBinaryData>(tolua_S, 2, "mw.BinaryData",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_md5'", nullptr);
            return 0;
        }
        std::string ret = cobj->md5(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.Crypto:md5",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_md5'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWCrypto_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWCrypto_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWCrypto* ret = mwframework::MWCrypto::getInstance();
        object_to_luaval<mwframework::MWCrypto>(tolua_S, "mw.Crypto",(mwframework::MWCrypto*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.Crypto:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWCrypto_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWCrypto_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWCrypto)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.Crypto",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWCrypto* self = (mwframework::MWCrypto*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWCrypto(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.Crypto");
    tolua_cclass(tolua_S,"Crypto","mw.Crypto","",nullptr);

    tolua_beginmodule(tolua_S,"Crypto");
        tolua_function(tolua_S,"encipherAes256",lua_mwframework_MWCrypto_encipherAes256);
        tolua_function(tolua_S,"decodeBase64",lua_mwframework_MWCrypto_decodeBase64);
        tolua_function(tolua_S,"decipherXxtea",lua_mwframework_MWCrypto_decipherXxtea);
        tolua_function(tolua_S,"md5String",lua_mwframework_MWCrypto_md5String);
        tolua_function(tolua_S,"md5File",lua_mwframework_MWCrypto_md5File);
        tolua_function(tolua_S,"encipherXxtea",lua_mwframework_MWCrypto_encipherXxtea);
        tolua_function(tolua_S,"getAes256KeyLength",lua_mwframework_MWCrypto_getAes256KeyLength);
        tolua_function(tolua_S,"decipherAes256",lua_mwframework_MWCrypto_decipherAes256);
        tolua_function(tolua_S,"encodeBase64",lua_mwframework_MWCrypto_encodeBase64);
        tolua_function(tolua_S,"md5",lua_mwframework_MWCrypto_md5);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWCrypto_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWCrypto).name();
    g_luaType[typeName] = "mw.Crypto";
    g_typeCast["Crypto"] = "mw.Crypto";
    return 1;
}

int lua_mwframework_MWUUIDGenerator_generateUUID(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWUUIDGenerator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.UUIDGenerator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWUUIDGenerator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWUUIDGenerator_generateUUID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWUUIDGenerator_generateUUID'", nullptr);
            return 0;
        }
        std::string ret = cobj->generateUUID();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.UUIDGenerator:generateUUID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWUUIDGenerator_generateUUID'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWUUIDGenerator_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.UUIDGenerator",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWUUIDGenerator_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWUUIDGenerator* ret = mwframework::MWUUIDGenerator::getInstance();
        object_to_luaval<mwframework::MWUUIDGenerator>(tolua_S, "mw.UUIDGenerator",(mwframework::MWUUIDGenerator*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.UUIDGenerator:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWUUIDGenerator_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWUUIDGenerator_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWUUIDGenerator)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.UUIDGenerator",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWUUIDGenerator* self = (mwframework::MWUUIDGenerator*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWUUIDGenerator(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.UUIDGenerator");
    tolua_cclass(tolua_S,"UUIDGenerator","mw.UUIDGenerator","",nullptr);

    tolua_beginmodule(tolua_S,"UUIDGenerator");
        tolua_function(tolua_S,"generateUUID",lua_mwframework_MWUUIDGenerator_generateUUID);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWUUIDGenerator_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWUUIDGenerator).name();
    g_luaType[typeName] = "mw.UUIDGenerator";
    g_typeCast["UUIDGenerator"] = "mw.UUIDGenerator";
    return 1;
}

int lua_mwframework_MWAssetManager_checkVersion(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_checkVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_checkVersion'", nullptr);
            return 0;
        }
        cobj->checkVersion();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:checkVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_checkVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_setBundleVersion(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_setBundleVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.AssetManager:setBundleVersion");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_setBundleVersion'", nullptr);
            return 0;
        }
        cobj->setBundleVersion(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:setBundleVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_setBundleVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_getAssetRootPath(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_getAssetRootPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_getAssetRootPath'", nullptr);
            return 0;
        }
        std::string ret = cobj->getAssetRootPath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:getAssetRootPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_getAssetRootPath'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_getServerUrl(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_getServerUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_getServerUrl'", nullptr);
            return 0;
        }
        std::string ret = cobj->getServerUrl();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:getServerUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_getServerUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_setAssetRootPath(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_setAssetRootPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.AssetManager:setAssetRootPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_setAssetRootPath'", nullptr);
            return 0;
        }
        cobj->setAssetRootPath(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:setAssetRootPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_setAssetRootPath'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_beginUpdate(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_beginUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_beginUpdate'", nullptr);
            return 0;
        }
        cobj->beginUpdate();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:beginUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_beginUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_setServerUrl(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_setServerUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.AssetManager:setServerUrl");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_setServerUrl'", nullptr);
            return 0;
        }
        cobj->setServerUrl(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:setServerUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_setServerUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_setDevelopMode(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_setDevelopMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "mw.AssetManager:setDevelopMode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_setDevelopMode'", nullptr);
            return 0;
        }
        cobj->setDevelopMode(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:setDevelopMode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_setDevelopMode'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_getBundleVersion(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_getBundleVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_getBundleVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getBundleVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:getBundleVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_getBundleVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_setProgramVersion(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_setProgramVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "mw.AssetManager:setProgramVersion");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_setProgramVersion'", nullptr);
            return 0;
        }
        cobj->setProgramVersion(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:setProgramVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_setProgramVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_isDevelopMode(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_isDevelopMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_isDevelopMode'", nullptr);
            return 0;
        }
        bool ret = cobj->isDevelopMode();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:isDevelopMode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_isDevelopMode'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_getProgramVersion(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWAssetManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWAssetManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWAssetManager_getProgramVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_getProgramVersion'", nullptr);
            return 0;
        }
        int ret = cobj->getProgramVersion();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.AssetManager:getProgramVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_getProgramVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWAssetManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.AssetManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWAssetManager_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWAssetManager* ret = mwframework::MWAssetManager::getInstance();
        object_to_luaval<mwframework::MWAssetManager>(tolua_S, "mw.AssetManager",(mwframework::MWAssetManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.AssetManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWAssetManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWAssetManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWAssetManager)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.AssetManager",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWAssetManager* self = (mwframework::MWAssetManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWAssetManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.AssetManager");
    tolua_cclass(tolua_S,"AssetManager","mw.AssetManager","",nullptr);

    tolua_beginmodule(tolua_S,"AssetManager");
        tolua_function(tolua_S,"checkVersion",lua_mwframework_MWAssetManager_checkVersion);
        tolua_function(tolua_S,"setBundleVersion",lua_mwframework_MWAssetManager_setBundleVersion);
        tolua_function(tolua_S,"getAssetRootPath",lua_mwframework_MWAssetManager_getAssetRootPath);
        tolua_function(tolua_S,"getServerUrl",lua_mwframework_MWAssetManager_getServerUrl);
        tolua_function(tolua_S,"setAssetRootPath",lua_mwframework_MWAssetManager_setAssetRootPath);
        tolua_function(tolua_S,"beginUpdate",lua_mwframework_MWAssetManager_beginUpdate);
        tolua_function(tolua_S,"setServerUrl",lua_mwframework_MWAssetManager_setServerUrl);
        tolua_function(tolua_S,"setDevelopMode",lua_mwframework_MWAssetManager_setDevelopMode);
        tolua_function(tolua_S,"getBundleVersion",lua_mwframework_MWAssetManager_getBundleVersion);
        tolua_function(tolua_S,"setProgramVersion",lua_mwframework_MWAssetManager_setProgramVersion);
        tolua_function(tolua_S,"isDevelopMode",lua_mwframework_MWAssetManager_isDevelopMode);
        tolua_function(tolua_S,"getProgramVersion",lua_mwframework_MWAssetManager_getProgramVersion);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWAssetManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWAssetManager).name();
    g_luaType[typeName] = "mw.AssetManager";
    g_typeCast["AssetManager"] = "mw.AssetManager";
    return 1;
}

int lua_mwframework_MWNetHandler_create(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetHandler* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetHandler",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetHandler*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetHandler_create'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetHandler_create'", nullptr);
            return 0;
        }
        mwframework::MWNetHandler* ret = cobj->create();
        object_to_luaval<mwframework::MWNetHandler>(tolua_S, "mw.NetHandler",(mwframework::MWNetHandler*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetHandler:create",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetHandler_create'.",&tolua_err);
#endif

    return 0;
}
static int lua_mwframework_MWNetHandler_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWNetHandler)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.NetHandler",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWNetHandler* self = (mwframework::MWNetHandler*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWNetHandler(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.NetHandler");
    tolua_cclass(tolua_S,"NetHandler","mw.NetHandler","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"NetHandler");
        tolua_function(tolua_S,"create",lua_mwframework_MWNetHandler_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWNetHandler).name();
    g_luaType[typeName] = "mw.NetHandler";
    g_typeCast["NetHandler"] = "mw.NetHandler";
    return 1;
}

int lua_mwframework_MWNetRequest_getProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetRequest_getProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetRequest_getProtocolId'", nullptr);
            return 0;
        }
        std::string ret = cobj->getProtocolId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetRequest:getProtocolId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetRequest_getProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetRequest_setBody(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetRequest_setBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetRequest:setBody");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetRequest_setBody'", nullptr);
            return 0;
        }
        cobj->setBody(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetRequest:setBody",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetRequest_setBody'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetRequest_setProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetRequest_setProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetRequest:setProtocolId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetRequest_setProtocolId'", nullptr);
            return 0;
        }
        cobj->setProtocolId(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetRequest:setProtocolId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetRequest_setProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetRequest_getBody(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetRequest_getBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetRequest_getBody'", nullptr);
            return 0;
        }
        std::string ret = cobj->getBody();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetRequest:getBody",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetRequest_getBody'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetRequest_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.NetRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetRequest:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.NetRequest:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetRequest_create'", nullptr);
            return 0;
        }
        mwframework::MWNetRequest* ret = mwframework::MWNetRequest::create(arg0, arg1);
        object_to_luaval<mwframework::MWNetRequest>(tolua_S, "mw.NetRequest",(mwframework::MWNetRequest*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.NetRequest:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetRequest_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWNetRequest_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWNetRequest)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.NetRequest",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWNetRequest* self = (mwframework::MWNetRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWNetRequest(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.NetRequest");
    tolua_cclass(tolua_S,"NetRequest","mw.NetRequest","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"NetRequest");
        tolua_function(tolua_S,"getProtocolId",lua_mwframework_MWNetRequest_getProtocolId);
        tolua_function(tolua_S,"setBody",lua_mwframework_MWNetRequest_setBody);
        tolua_function(tolua_S,"setProtocolId",lua_mwframework_MWNetRequest_setProtocolId);
        tolua_function(tolua_S,"getBody",lua_mwframework_MWNetRequest_getBody);
        tolua_function(tolua_S,"create", lua_mwframework_MWNetRequest_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWNetRequest).name();
    g_luaType[typeName] = "mw.NetRequest";
    g_typeCast["NetRequest"] = "mw.NetRequest";
    return 1;
}

int lua_mwframework_MWNetResponse_getRelatedRequest(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetResponse_getRelatedRequest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetResponse_getRelatedRequest'", nullptr);
            return 0;
        }
        mwframework::MWNetRequest* ret = cobj->getRelatedRequest();
        object_to_luaval<mwframework::MWNetRequest>(tolua_S, "mw.NetRequest",(mwframework::MWNetRequest*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetResponse:getRelatedRequest",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetResponse_getRelatedRequest'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetResponse_getProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetResponse_getProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetResponse_getProtocolId'", nullptr);
            return 0;
        }
        std::string ret = cobj->getProtocolId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetResponse:getProtocolId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetResponse_getProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetResponse_setBody(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetResponse_setBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetResponse:setBody");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetResponse_setBody'", nullptr);
            return 0;
        }
        cobj->setBody(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetResponse:setBody",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetResponse_setBody'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetResponse_setProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetResponse_setProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetResponse:setProtocolId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetResponse_setProtocolId'", nullptr);
            return 0;
        }
        cobj->setProtocolId(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetResponse:setProtocolId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetResponse_setProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetResponse_getBody(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetResponse* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetResponse*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetResponse_getBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetResponse_getBody'", nullptr);
            return 0;
        }
        std::string ret = cobj->getBody();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetResponse:getBody",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetResponse_getBody'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetResponse_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.NetResponse",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        mwframework::MWNetRequest* arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetResponse:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.NetResponse:create");
        ok &= luaval_to_object<mwframework::MWNetRequest>(tolua_S, 4, "mw.NetRequest",&arg2);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetResponse_create'", nullptr);
            return 0;
        }
        mwframework::MWNetResponse* ret = mwframework::MWNetResponse::create(arg0, arg1, arg2);
        object_to_luaval<mwframework::MWNetResponse>(tolua_S, "mw.NetResponse",(mwframework::MWNetResponse*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.NetResponse:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetResponse_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWNetResponse_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWNetResponse)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.NetResponse",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWNetResponse* self = (mwframework::MWNetResponse*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWNetResponse(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.NetResponse");
    tolua_cclass(tolua_S,"NetResponse","mw.NetResponse","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"NetResponse");
        tolua_function(tolua_S,"getRelatedRequest",lua_mwframework_MWNetResponse_getRelatedRequest);
        tolua_function(tolua_S,"getProtocolId",lua_mwframework_MWNetResponse_getProtocolId);
        tolua_function(tolua_S,"setBody",lua_mwframework_MWNetResponse_setBody);
        tolua_function(tolua_S,"setProtocolId",lua_mwframework_MWNetResponse_setProtocolId);
        tolua_function(tolua_S,"getBody",lua_mwframework_MWNetResponse_getBody);
        tolua_function(tolua_S,"create", lua_mwframework_MWNetResponse_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWNetResponse).name();
    g_luaType[typeName] = "mw.NetResponse";
    g_typeCast["NetResponse"] = "mw.NetResponse";
    return 1;
}

int lua_mwframework_MWNetProtocol_getRelatedHandler(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetProtocol_getRelatedHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetProtocol_getRelatedHandler'", nullptr);
            return 0;
        }
        mwframework::MWNetHandler* ret = cobj->getRelatedHandler();
        object_to_luaval<mwframework::MWNetHandler>(tolua_S, "mw.NetHandler",(mwframework::MWNetHandler*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetProtocol:getRelatedHandler",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetProtocol_getRelatedHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetProtocol_getServiceId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetProtocol_getServiceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetProtocol_getServiceId'", nullptr);
            return 0;
        }
        std::string ret = cobj->getServiceId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetProtocol:getServiceId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetProtocol_getServiceId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetProtocol_getProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetProtocol_getProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetProtocol_getProtocolId'", nullptr);
            return 0;
        }
        std::string ret = cobj->getProtocolId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetProtocol:getProtocolId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetProtocol_getProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetProtocol_setServiceId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetProtocol_setServiceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetProtocol:setServiceId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetProtocol_setServiceId'", nullptr);
            return 0;
        }
        cobj->setServiceId(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetProtocol:setServiceId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetProtocol_setServiceId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetProtocol_setProtocolId(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetProtocol_setProtocolId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetProtocol:setProtocolId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetProtocol_setProtocolId'", nullptr);
            return 0;
        }
        cobj->setProtocolId(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetProtocol:setProtocolId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetProtocol_setProtocolId'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetProtocol_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.NetProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        mwframework::MWNetHandler* arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetProtocol:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.NetProtocol:create");
        ok &= luaval_to_object<mwframework::MWNetHandler>(tolua_S, 4, "mw.NetHandler",&arg2);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetProtocol_create'", nullptr);
            return 0;
        }
        mwframework::MWNetProtocol* ret = mwframework::MWNetProtocol::create(arg0, arg1, arg2);
        object_to_luaval<mwframework::MWNetProtocol>(tolua_S, "mw.NetProtocol",(mwframework::MWNetProtocol*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.NetProtocol:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetProtocol_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWNetProtocol_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWNetProtocol)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.NetProtocol",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWNetProtocol* self = (mwframework::MWNetProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWNetProtocol(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.NetProtocol");
    tolua_cclass(tolua_S,"NetProtocol","mw.NetProtocol","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"NetProtocol");
        tolua_function(tolua_S,"getRelatedHandler",lua_mwframework_MWNetProtocol_getRelatedHandler);
        tolua_function(tolua_S,"getServiceId",lua_mwframework_MWNetProtocol_getServiceId);
        tolua_function(tolua_S,"getProtocolId",lua_mwframework_MWNetProtocol_getProtocolId);
        tolua_function(tolua_S,"setServiceId",lua_mwframework_MWNetProtocol_setServiceId);
        tolua_function(tolua_S,"setProtocolId",lua_mwframework_MWNetProtocol_setProtocolId);
        tolua_function(tolua_S,"create", lua_mwframework_MWNetProtocol_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWNetProtocol).name();
    g_luaType[typeName] = "mw.NetProtocol";
    g_typeCast["NetProtocol"] = "mw.NetProtocol";
    return 1;
}

int lua_mwframework_MWNetCenter_addNetService(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_addNetService'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        mwframework::MWNetService* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetCenter:addNetService");

        ok &= luaval_to_object<mwframework::MWNetService>(tolua_S, 3, "mw.NetService",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_addNetService'", nullptr);
            return 0;
        }
        cobj->addNetService(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:addNetService",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_addNetService'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_removeAllNetFilters(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_removeAllNetFilters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_removeAllNetFilters'", nullptr);
            return 0;
        }
        cobj->removeAllNetFilters();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:removeAllNetFilters",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_removeAllNetFilters'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_addNetFilter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_addNetFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWNetFilter* arg0;

        ok &= luaval_to_object<mwframework::MWNetFilter>(tolua_S, 2, "mw.NetFilter",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_addNetFilter'", nullptr);
            return 0;
        }
        cobj->addNetFilter(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:addNetFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_addNetFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_removeNetProtocol(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_removeNetProtocol'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetCenter:removeNetProtocol");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_removeNetProtocol'", nullptr);
            return 0;
        }
        cobj->removeNetProtocol(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:removeNetProtocol",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_removeNetProtocol'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_removeNetFilter(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_removeNetFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWNetFilter* arg0;

        ok &= luaval_to_object<mwframework::MWNetFilter>(tolua_S, 2, "mw.NetFilter",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_removeNetFilter'", nullptr);
            return 0;
        }
        cobj->removeNetFilter(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:removeNetFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_removeNetFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_removeNetService(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_removeNetService'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetCenter:removeNetService");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_removeNetService'", nullptr);
            return 0;
        }
        cobj->removeNetService(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:removeNetService",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_removeNetService'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_sendMessage(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_sendMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWNetRequest* arg0;

        ok &= luaval_to_object<mwframework::MWNetRequest>(tolua_S, 2, "mw.NetRequest",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_sendMessage'", nullptr);
            return 0;
        }
        cobj->sendMessage(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:sendMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_sendMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_addNetProtocol(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_addNetProtocol'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            mwframework::MWNetProtocol* arg0;
            ok &= luaval_to_object<mwframework::MWNetProtocol>(tolua_S, 2, "mw.NetProtocol",&arg0);

            if (!ok) { break; }
            cobj->addNetProtocol(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetCenter:addNetProtocol");

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.NetCenter:addNetProtocol");

            if (!ok) { break; }
            mwframework::MWNetHandler* arg2;
            ok &= luaval_to_object<mwframework::MWNetHandler>(tolua_S, 4, "mw.NetHandler",&arg2);

            if (!ok) { break; }
            cobj->addNetProtocol(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "mw.NetCenter:addNetProtocol",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_addNetProtocol'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_dispatchFailedMessage(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_dispatchFailedMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWNetResponse* arg0;

        ok &= luaval_to_object<mwframework::MWNetResponse>(tolua_S, 2, "mw.NetResponse",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_dispatchFailedMessage'", nullptr);
            return 0;
        }
        cobj->dispatchFailedMessage(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:dispatchFailedMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_dispatchFailedMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_dispatchSuccessfulMessage(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_dispatchSuccessfulMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        mwframework::MWNetResponse* arg0;

        ok &= luaval_to_object<mwframework::MWNetResponse>(tolua_S, 2, "mw.NetResponse",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_dispatchSuccessfulMessage'", nullptr);
            return 0;
        }
        cobj->dispatchSuccessfulMessage(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:dispatchSuccessfulMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_dispatchSuccessfulMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_sendCommand(lua_State* tolua_S)
{
    int argc = 0;
    mwframework::MWNetCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (mwframework::MWNetCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_mwframework_MWNetCenter_sendCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        cocos2d::Ref* arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "mw.NetCenter:sendCommand");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "mw.NetCenter:sendCommand");

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 4, "cc.Ref",&arg2);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_sendCommand'", nullptr);
            return 0;
        }
        cobj->sendCommand(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "mw.NetCenter:sendCommand",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_sendCommand'.",&tolua_err);
#endif

    return 0;
}
int lua_mwframework_MWNetCenter_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"mw.NetCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_mwframework_MWNetCenter_getInstance'", nullptr);
            return 0;
        }
        mwframework::MWNetCenter* ret = mwframework::MWNetCenter::getInstance();
        object_to_luaval<mwframework::MWNetCenter>(tolua_S, "mw.NetCenter",(mwframework::MWNetCenter*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "mw.NetCenter:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_mwframework_MWNetCenter_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_mwframework_MWNetCenter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MWNetCenter)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"mw.NetCenter",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        mwframework::MWNetCenter* self = (mwframework::MWNetCenter*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_mwframework_MWNetCenter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"mw.NetCenter");
    tolua_cclass(tolua_S,"NetCenter","mw.NetCenter","mw.Object",nullptr);

    tolua_beginmodule(tolua_S,"NetCenter");
        tolua_function(tolua_S,"addNetService",lua_mwframework_MWNetCenter_addNetService);
        tolua_function(tolua_S,"removeAllNetFilters",lua_mwframework_MWNetCenter_removeAllNetFilters);
        tolua_function(tolua_S,"addNetFilter",lua_mwframework_MWNetCenter_addNetFilter);
        tolua_function(tolua_S,"removeNetProtocol",lua_mwframework_MWNetCenter_removeNetProtocol);
        tolua_function(tolua_S,"removeNetFilter",lua_mwframework_MWNetCenter_removeNetFilter);
        tolua_function(tolua_S,"removeNetService",lua_mwframework_MWNetCenter_removeNetService);
        tolua_function(tolua_S,"sendMessage",lua_mwframework_MWNetCenter_sendMessage);
        tolua_function(tolua_S,"addNetProtocol",lua_mwframework_MWNetCenter_addNetProtocol);
        tolua_function(tolua_S,"dispatchFailedMessage",lua_mwframework_MWNetCenter_dispatchFailedMessage);
        tolua_function(tolua_S,"dispatchSuccessfulMessage",lua_mwframework_MWNetCenter_dispatchSuccessfulMessage);
        tolua_function(tolua_S,"sendCommand",lua_mwframework_MWNetCenter_sendCommand);
        tolua_function(tolua_S,"getInstance", lua_mwframework_MWNetCenter_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(mwframework::MWNetCenter).name();
    g_luaType[typeName] = "mw.NetCenter";
    g_typeCast["NetCenter"] = "mw.NetCenter";
    return 1;
}
TOLUA_API int register_all_mwframework(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"mw",0);
	tolua_beginmodule(tolua_S,"mw");

	lua_register_mwframework_MWObject(tolua_S);
	lua_register_mwframework_MWViewSegue(tolua_S);
	lua_register_mwframework_MWNetRequest(tolua_S);
	lua_register_mwframework_MWGameView(tolua_S);
	lua_register_mwframework_MWGifFrame(tolua_S);
	lua_register_mwframework_MWException(tolua_S);
	lua_register_mwframework_MWGifFramesCache(tolua_S);
	lua_register_mwframework_MWUUIDGenerator(tolua_S);
	lua_register_mwframework_MWGameScene(tolua_S);
	lua_register_mwframework_MWSvgSprite(tolua_S);
	lua_register_mwframework_MWDictionary(tolua_S);
	lua_register_mwframework_MWNetHandler(tolua_S);
	lua_register_mwframework_MWSystemHelper(tolua_S);
	lua_register_mwframework_MWGifSprite(tolua_S);
	lua_register_mwframework_MWBinaryData(tolua_S);
	lua_register_mwframework_MWSqliteDb(tolua_S);
	lua_register_mwframework_MWQueue(tolua_S);
	lua_register_mwframework_MWNetCenter(tolua_S);
	lua_register_mwframework_MWViewController(tolua_S);
	lua_register_mwframework_MWNetProtocol(tolua_S);
	lua_register_mwframework_MWIOUtils(tolua_S);
	lua_register_mwframework_MWStack(tolua_S);
	lua_register_mwframework_MWArrayList(tolua_S);
	lua_register_mwframework_MWJsonArray(tolua_S);
	lua_register_mwframework_MWAssetManager(tolua_S);
	lua_register_mwframework_MWZipData(tolua_S);
	lua_register_mwframework_MWCrypto(tolua_S);
	lua_register_mwframework_MWNetResponse(tolua_S);
	lua_register_mwframework_MWJsonObject(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

