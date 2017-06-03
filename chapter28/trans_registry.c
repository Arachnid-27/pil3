/* exercise 28.4 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

static const char *table_key = "k";

static int l_settrans(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_pushlightuserdata(L, (void*) &table_key);
    lua_insert(L, 1);
    lua_settable(L, LUA_REGISTRYINDEX);
    return 0;
}

static int l_gettrans(lua_State* L) {
    lua_pushlightuserdata(L, (void*) &table_key);
    lua_gettable(L, LUA_REGISTRYINDEX);
    return 1;
}

static int l_transliterate(lua_State* L) {
    static char key[] = "k";

    size_t l;
    luaL_Buffer b;
    const char *s = luaL_checklstring(L, 1, &l);
    l_gettrans(L);
    luaL_buffinit(L, &b);

    for (size_t i = 0; i < l; ++i) {
        key[0] = s[i];
        lua_getfield(L, 2, key);
        if (lua_isnil(L, -1)) {
            luaL_addstring(&b, key);
        } else if (lua_toboolean(L, -1)) {
            luaL_addstring(&b, lua_tostring(L,  -1));
        }
        lua_pop(L, 1);
    }

    luaL_pushresult(&b);
    return 1;
}

const char* script = "settrans({ a = 'd', b = false })      \
                      print(gettrans())                     \
                      print(transliterate('abcdcba'))";

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_settrans);
    lua_setglobal(L, "settrans");
    lua_pushcfunction(L, l_gettrans);
    lua_setglobal(L, "gettrans");
    lua_pushcfunction(L, l_transliterate);
    lua_setglobal(L, "transliterate");

    error = luaL_dostring(L, script);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
