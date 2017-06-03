/* exercise 28.5 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

static int l_transliterate(lua_State* L) {
    static char key[] = "k";

    size_t l;
    luaL_Buffer b;
    const char *s = luaL_checklstring(L, 1, &l);
    luaL_buffinit(L, &b);

    for (size_t i = 0; i < l; ++i) {
        key[0] = s[i];
        lua_getfield(L, lua_upvalueindex(1), key);
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

static int l_settrans(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_pushcclosure(L, l_transliterate, 1);
    return 1;
}

const char* script = "transliterate = settrans({ a = 'd', b = false })      \
                      print(transliterate('abcdcba'))                       \
                      transliterate = settrans({ a = false, c = 'd' })      \
                      print(transliterate('abcdcba'))";

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_settrans);
    lua_setglobal(L, "settrans");

    error = luaL_dostring(L, script);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
