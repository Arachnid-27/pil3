/* exercise 27.5 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

const char* script = "f = function (...) print(...) coroutine.yield() end   \
                      c = coroutine.create(function (t) foreach(t, f) end)  \
                      coroutine.resume(c, {x = 10, y = 20, z = 30})         \
                      coroutine.resume(c)                                   \
                      coroutine.resume(c)";

static int _foreach(lua_State* L, lua_CFunction k) {
    while (lua_next(L, 1)) {
        if (lua_isnil(L, -1)) {
            break;
        }

        lua_pushvalue(L, 2);
        lua_insert(L, -2);
        lua_pushvalue(L, -3);
        lua_insert(L, -2);
        lua_callk(L, 2, 0, 0, k);
    }
    return 0;
}

static int l_foreach_c(lua_State* L) {
    return _foreach(L, l_foreach_c);
}

static int l_foreach(lua_State* L) {
    lua_pushnil(L);
    return _foreach(L, l_foreach_c);
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
