/* exercise 27.2 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

static int l_table_pack(lua_State* L) {
    int n = lua_gettop(L);

    lua_createtable(L, n, 1);
    lua_insert(L, 1);

    lua_pushstring(L, "n");
    lua_pushnumber(L, n);
    lua_settable(L, 1);

    for (int i = n; i >= 1; --i) {
        lua_pushnumber(L, i);
        lua_insert(L, -2);
        lua_settable(L, 1);
    }

    return 1;
}

const char* script = "t = table_pack('a', 'b', 'c') \
                      print(t.n)                    \
                      print(#t)                     \
                      print(table.unpack(t))";

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_table_pack);
    lua_setglobal(L, "table_pack");

    error = luaL_dostring(L, script);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}

