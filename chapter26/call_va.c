/* exercise 26.2 */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

void error(lua_State* L, const char* fmt, ...);

void call_va(lua_State* L, const char* func, const char* sig, ...) {
    va_list args;
    int narg, nres;

    va_start(args, sig);
    lua_getglobal(L, func);

    for (narg = 0; *sig; ++narg) {
        luaL_checkstack(L, 1, "too many arguments");

        switch (*sig) {
        case 'b':
            lua_pushboolean(L, va_arg(args, int));
            break;
        case 'd':
            lua_pushnumber(L, va_arg(args, double));
            break;
        case 'i':
            lua_pushinteger(L, va_arg(args, int));
            break;
        case 's':
            lua_pushstring(L, va_arg(args, char*));
            break;
        case '>':
            goto endargs;
        default:
            error(L, "invalid option (%c)", *(sig - 1));
        }
    }

endargs:

    nres = strlen(sig);

    if (lua_pcall(L, narg, nres, 0) != 0) {
        error(L, "error calling '%s': %s", func, lua_tostring(L, -1));
    }

    nres = -nres;
    while (*sig) {
        switch (*sig++) {
        case 'b': {
            int n = lua_toboolean(L, nres);
            *va_arg(args, int*) = n;
            break;
        }
        case 'd': {
            int isnum;
            double n = lua_tonumberx(L, nres, &isnum);
            if (!isnum) {
                error(L, "wrong result type");
            }
            *va_arg(args, double*) = n;
            break;
        }
        case 'i': {
            int isnum;
            int n = lua_tointegerx(L, nres, &isnum);
            if (!isnum) {
                error(L, "wrong result type");
            }
            *va_arg(args, int*) = n;
            break;
        }
        case 's': {
            const char *s = lua_tostring(L, nres);
            if (s == NULL) {
                error(L, "wrong result type");
            }
            *va_arg(args, const char**) = s;
        }
        default:
            error(L, "invalid option (%c)", *(sig - 1));
        }
        ++nres;
    }

    va_end(args);
}

void error(lua_State* L, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    lua_close(L);
    exit(EXIT_FAILURE);
}
