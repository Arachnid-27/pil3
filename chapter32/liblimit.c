/* exercise 32.1 */

#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"

typedef struct {
    size_t used;
    size_t limit;
    lua_Alloc old;
} Counter;

void *l_limitalloc(void *ud, void *ptr, size_t osize, size_t nsize) {
    Counter *c = (Counter*) ud;
    if (nsize == 0) {
        free(ptr);
        c->used -= osize;
        return NULL;
    } else {
        if (c->limit != 0 && c->used - osize + nsize > c->limit) {
            return NULL;
        }
        ptr = realloc(ptr, nsize);
        if (ptr != NULL) {
            c->used = c->used - osize + nsize;
        }
        return ptr;
    }
}

static int l_setlimit(lua_State* L) {
    int limit = luaL_checkint(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "__counter");
    Counter *c = (Counter*) lua_touserdata(L, -1);
    c->limit = limit;
    return 0;
}

static int l_getlimit(lua_State* L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "__counter");
    Counter *c = (Counter*) lua_touserdata(L, -1);
    lua_pushnumber(L, c->limit);
    return 1;
}

static int l_getused(lua_State* L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "__counter");
    Counter *c = (Counter*) lua_touserdata(L, -1);
    lua_pushnumber(L, c->used);
    return 1;
}

static int l_gc(lua_State* L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "__counter");
    Counter *c = (Counter*) lua_touserdata(L, -1);
    lua_setallocf(L, c->old, NULL);
    return 0;
}

static const struct luaL_Reg l_funcs[] = {
    {"setlimit", l_setlimit},
    {"getlimit", l_getlimit},
    {"getused", l_getused},
    {NULL, NULL}
};

int luaopen_liblimit(lua_State* L) {
    Counter *c = (Counter*) lua_newuserdata(L, sizeof(Counter));
    lua_setfield(L, LUA_REGISTRYINDEX, "__counter");
    c->limit = 0;
    c->used = lua_gc(L, LUA_GCCOUNT, 0) * 1024 + lua_gc(L, LUA_GCCOUNTB, 0);
    c->old = lua_getallocf(L, NULL);
    lua_setallocf(L, l_limitalloc, c);

    lua_newtable(L);
    lua_pushcfunction(L, l_gc);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -1);

    luaL_newlib(L, l_funcs);
    return 1;
}
