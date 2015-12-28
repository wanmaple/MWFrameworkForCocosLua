#include "base/ccConfig.h"
#ifndef __pbc_lua_h__
#define __pbc_lua_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
    
    int luaopen_protobuf_c(lua_State *L);
    
#ifdef __cplusplus
}
#endif

#endif