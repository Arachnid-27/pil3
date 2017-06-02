/* exercise 27.1 */

#include <stdio.h>
#include <stdlib.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

const char* script[] = {
    "print(summation())",
    "print(summation(2.3, 5.4))",
    "print(summation(2.3, 5.4, -34))",
    "print(summation(2.3, 5.4, {}))"
};

static int l_summation(lua_State* L) {
    int n = lua_gettop(L);
    double sum = 0;

    for (int i = 1; i <= n; ++i) {
        double num = luaL_checknumber(L, i);
        sum += num;
    }

    lua_pushnumber(L, sum);
    return 1;
}

int main(int argc, char* argv[]) {
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_summation);
    lua_setglobal(L, "summation");

    for (int i = 0; i < 4; ++i) {
        error = luaL_dostring(L, script[i]);
        if (error) {
            printf("%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
            exit(EXIT_FAILURE);
        }
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
