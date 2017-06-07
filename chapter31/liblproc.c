/* exercise 31.2 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "lua5.2/lua.h"
#include "lua5.2/lauxlib.h"
#include "lua5.2/lualib.h"

typedef struct Proc {
    lua_State *L;
    pthread_t thread;
    pthread_cond_t cond;
    const char *channel;
    struct Proc *prev, *next;
} Proc;

static Proc *waitsend = NULL;
static Proc *waitrecv = NULL;

static pthread_mutex_t kernel_access = PTHREAD_MUTEX_INITIALIZER;

static Proc* getself(lua_State* L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "_SELF");
    Proc *p = (Proc*) lua_touserdata(L, -1);
    lua_pop(L, 1);
    return p;
}

static void movevalues(lua_State* send, lua_State* recv) {
    int n = lua_gettop(send);
    lua_State *temp = luaL_newstate();
    lua_xmove(send, temp, n - 1);
    lua_xmove(temp, recv, n - 1);
    lua_close(temp);
}

static Proc* searchmatch(const char* channel, Proc** list) {
    Proc *node = *list;

    if (node != NULL) {
        do {
            if (strcmp(channel, node->channel) == 0) {
                if (node->next == node) {
                    *list = NULL;
                } else {
                    *list = node->next;
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
                return node;
            }
            node = node->next;
        } while(node != *list);
    }

    return NULL;
}

static void waitonlist(lua_State* L, const char* channel, Proc** list) {
    Proc *p = getself(L);

    if (*list == NULL) {
        *list = p;
        p->prev = p->next = p;
    } else {
        p->prev = (*list)->prev;
        p->next = *list;
        p->prev->next = p->next->prev = p;
    }

    p->channel = channel;

    do {
        pthread_cond_wait(&p->cond, &kernel_access);
    } while (p->channel);
}

static int ll_send(lua_State* L) {
    const char *channel = luaL_checkstring(L, 1);

    pthread_mutex_lock(&kernel_access);

    Proc *p = searchmatch(channel, &waitrecv);
    if (p) {
        movevalues(L, p->L);
        p->channel = NULL;
        pthread_cond_signal(&p->cond);
    } else {
        waitonlist(L, channel, &waitsend);
    }

    pthread_mutex_unlock(&kernel_access);
    return 0;
}

static int ll_recv(lua_State* L) {
    const char *channel = luaL_checkstring(L, 1);
    lua_settop(L, 1);

    pthread_mutex_lock(&kernel_access);

    Proc *p = searchmatch(channel, &waitsend);
    if (p) {
        movevalues(p->L, L);
        p->channel = NULL;
        pthread_cond_signal(&p->cond);
    } else {
        waitonlist(L, channel, &waitrecv);
    }

    pthread_mutex_unlock(&kernel_access);
    return lua_gettop(L) - 1;
}

int luaopen_liblproc(lua_State* L);

static void* ll_thread(void* arg) {
    lua_State *L = (lua_State*) arg;
    luaL_openlibs(L);
    luaL_requiref(L, "liblproc", luaopen_liblproc, 1);
    lua_pop(L, 1);
    if (lua_pcall(L, 0, 0, 0) != 0) {
        fprintf(stderr, "thread error: %s", lua_tostring(L, -1));
    }
    pthread_cond_destroy(&getself(L)->cond);
    lua_close(L);
    return NULL;
}

static int ll_start(lua_State* L) {
    pthread_t thread;
    const char *chunk = luaL_checkstring(L, 1);
    lua_State *L1 = luaL_newstate();

    if (L1 == NULL) {
        luaL_error(L, "unable to create new state");
    }

    if (luaL_loadstring(L1, chunk) != 0) {
        luaL_error(L, "error starting thread: %s", lua_tostring(L1, -1));
    }

    if (pthread_create(&thread, NULL, ll_thread, L1) != 0) {
        luaL_error(L, "unable to create new state");
    }

    pthread_detach(thread);
    return 0;
}

static int ll_exit(lua_State* L) {
    pthread_exit(NULL);
    return 0;
}

static const struct luaL_Reg ll_funcs[] = {
    {"start", ll_start},
    {"send", ll_send},
    {"recv", ll_recv},
    {"exit", ll_exit},
    {NULL, NULL}
};

int luaopen_liblproc(lua_State* L) {
    Proc *self = (Proc*) lua_newuserdata(L, sizeof(Proc));
    lua_setfield(L, LUA_REGISTRYINDEX, "_SELF");
    self->L = L;
    self->thread = pthread_self();
    self->channel = NULL;
    pthread_cond_init(&self->cond, NULL);
    luaL_newlib(L, ll_funcs);
    return 1;
}
