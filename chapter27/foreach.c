/* exercise 27.4 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

const char* script = "foreach({x = 10, y = 20, z = 30}, print)";

static int l_foreach(lua_State* L) {
//  if (lua_gettop(L) != 2) {
//  }

    lua_pushnil(L);
    while (lua_next(L, 1)) {
        if (lua_isnil(L, -1)) {
            break;
        }

        lua_pushvalue(L, 2);
        lua_insert(L, -2);
        lua_pushvalue(L, -3);
        lua_insert(L, -2);
        lua_call(L, 2, 0);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_foreach);
    lua_setglobal(L, "foreach");

    error = luaL_dostring(L, script);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
