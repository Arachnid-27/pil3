/* exercise 26.1 */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

int main(int argc, char* argv[]) {
    int fd, error;
    char buf[1024];
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if ((fd = open("plot_function.lua", O_RDONLY)) == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    if (read(fd, buf, 1024) == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    error = luaL_dostring(L, buf);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(EXIT_FAILURE);
    }

    lua_getglobal(L, "f");
    lua_pushinteger(L, 20);

    error = lua_pcall(L, 1, 0, 0);
    if (error) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
    exit(EXIT_SUCCESS);
}
