/* exercise 27.3 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

static int l_reverse(lua_State* L) {
    int n = lua_gettop(L);
    int m = n / 2;
    lua_State *t = luaL_newstate();

    for (int i = m; i >= 1; --i) {
        lua_pushvalue(L, i);
    }
    lua_xmove(L, t, m);
    for (int i = 1; i <= m; ++i) {
        lua_replace(L, i);
    }
    lua_xmove(t, L, m);

    lua_close(t);
    return n;
}

const char* script = "print(reverse(\"left\", 1, \"hello\", 20, \"right\"))";

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_reverse);
    lua_setglobal(L, "reverse");

    error = luaL_dostring(L, script);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
