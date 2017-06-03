/* exercise 28.1 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

static int l_filter(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    int n = luaL_len(L, 1);

    lua_newtable(L);

    for (int i = 1, j = 1; i <= n; ++i) {
        lua_pushvalue(L, 2);
        lua_rawgeti(L, 1, i);
        lua_call(L, 1, 1);
        if (lua_toboolean(L, -1)) {
            lua_rawgeti(L, 1, i);
            lua_rawseti(L, 3, j++);
        }
        lua_pop(L, 1);
    }

    return 1;
}

const char* script = "print(table.unpack(filter({1, 3, 20, -4, 5}, function (x) return x < 5 end)))";

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_filter);
    lua_setglobal(L, "filter");

    error = luaL_dostring(L, script);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
