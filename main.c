#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "lib/events.h"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        return 1;
    }

    int error = 0;
    const char *fileName = argv[1];

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, lua_addEventHandler);
    lua_setglobal(L, "addEventHandler");

    if (luaL_dofile(L, fileName) != LUA_OK)
    {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        error = 1;
        goto err;
    }

    int handlerFnRef = getEventHandler("start");
    lua_rawgeti(L, LUA_REGISTRYINDEX, handlerFnRef);
    lua_pushstring(L, "world!");

    if (lua_pcall(L, 1, 0, 0) != LUA_OK)
    {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        error = 1;
        goto err;
    }

err:
    lua_close(L);

    return error;
}
