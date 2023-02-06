#pragma once
#define STB_DS_IMPLEMENTATION
#include "std_ds.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

struct eventMap
{
    const char *key;
    int value;
};

struct eventMap *map = NULL;

int getEventHandler(const char *eventName)
{
    return shget(map, eventName);
}

void addEventHandler(const char *eventName, int handlerFnRef)
{
    shput(map, eventName, handlerFnRef);
}

void removeEventHandler(const char *eventName, int handlerFnRef)
{
    shdel(map, eventName);
}

static int lua_addEventHandler(lua_State *L)
{
    const char* eventName = lua_tostring(L, 1);
    int handlerFnRef = luaL_ref(L, LUA_REGISTRYINDEX);
    addEventHandler(eventName, handlerFnRef);
    return 0;
}
