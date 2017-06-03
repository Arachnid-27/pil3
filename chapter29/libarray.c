/* exercise 29.1 29.2 29.3 */

#include <stdlib.h>
#include <string.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"

#define BITS_PER_WORD   (sizeof(unsigned int) << 3)
#define I_WORD(n)       ((unsigned int) (n) / BITS_PER_WORD)
#define I_BIT(n)        (1 << ((unsigned int) (n) % BITS_PER_WORD))

typedef struct NumArray {
    int size;
    unsigned int values[1];
} NumArray;

static NumArray* pusharray(lua_State* L, int n) {
    size_t bytes = sizeof(NumArray) + I_WORD(n - 1) * sizeof(unsigned int);
    NumArray *arr = (NumArray*) lua_newuserdata(L, bytes);
    memset(arr, 0, bytes);
    arr->size = n;

    luaL_getmetatable(L, "luaBook.array");
    lua_setmetatable(L, -2);
    return arr;
}

static int newarray(lua_State* L) {
    int n = luaL_checkint(L, 1);
    luaL_argcheck(L, n >= 1, 1, "invalid size");
    pusharray(L, n);
    return 1;
}

static int setarray(lua_State* L) {
    NumArray *arr = (NumArray*) luaL_checkudata(L, 1, "luaBook.array");
    int n = luaL_checkint(L, 2) - 1;
    luaL_argcheck(L, 0 <= n && n < arr->size, 2, "out of range");
    luaL_checktype(L, 3, LUA_TBOOLEAN);

    if (lua_toboolean(L, 3)) {
        arr->values[I_WORD(n)] |= I_BIT(n);
    } else {
        arr->values[I_WORD(n)] &= ~I_BIT(n);
    }
    return 0;
}

static int getarray(lua_State* L) {
    NumArray *arr = (NumArray*) luaL_checkudata(L, 1, "luaBook.array");
    int n = luaL_checkint(L, 2) - 1;
    luaL_argcheck(L, 0 <= n && n < arr->size, 2, "out of range");

    lua_pushboolean(L, arr->values[I_WORD(n)] & I_BIT(n));
    return 1;
}

static int getsize(lua_State* L) {
    NumArray *arr = (NumArray*) luaL_checkudata(L, 1, "luaBook.array");
    lua_pushinteger(L, arr->size);
    return 1;
}

static int unionarray(lua_State* L) {
    NumArray *arr1 = (NumArray*) luaL_checkudata(L, 1, "luaBook.array");
    NumArray *arr2 = (NumArray*) luaL_checkudata(L, 2, "luaBook.array");
    int n = arr1->size > arr2->size ? arr1->size : arr2->size;
    int m = arr1->size > arr2->size ? arr2->size : arr1->size;
    NumArray *left = arr1->size > arr2->size ? arr1 : arr2;
    NumArray *arr = pusharray(L, n);

    for (size_t i = 0; i <= I_WORD(m); ++i) {
        arr->values[i] = arr1->values[i] | arr2->values[i];
    }
    for (size_t i = I_WORD(m) + 1; i <= I_WORD(n); ++i) {
        arr->values[i] = left->values[i];
    }
    return 1;
}

static int intersectionarray(lua_State* L) {
    NumArray *arr1 = (NumArray*) luaL_checkudata(L, 1, "luaBook.array");
    NumArray *arr2 = (NumArray*) luaL_checkudata(L, 2, "luaBook.array");
    int n = arr1->size > arr2->size ? arr2->size : arr1->size;
    NumArray *arr = pusharray(L, n);

    for (size_t i = 0; i <= I_WORD(n); ++i) {
        arr->values[i] = arr1->values[i] & arr2->values[i];
    }
    return 1;
}

static int array2string(lua_State* L) {
    NumArray *arr = (NumArray*) luaL_checkudata(L, 1, "luaBook.array");
    luaL_Buffer b;
    luaL_buffinit(L, &b);

    for (int i = 0; i < arr->size; ++i) {
        luaL_addchar(&b, (arr->values[I_WORD(i)] & I_BIT(i)) ? '1' : '0');
    }

    luaL_pushresult(&b);
    return 1;
}

static const struct luaL_Reg arraylib_f[] = {
    {"new", newarray},
    {NULL, NULL}
};

static const struct luaL_Reg arraylib_m[] = {
    {"set", setarray},
    {"get", getarray},
    {"size", getsize},
    {"union", unionarray},
    {"intersection", intersectionarray},
    {"__tostring", array2string},
    {NULL, NULL}
};

int luaopen_libarray(lua_State* L) {
    luaL_newmetatable(L, "luaBook.array");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, arraylib_m, 0);

    luaL_newlib(L, arraylib_f);
    return 1;
}
