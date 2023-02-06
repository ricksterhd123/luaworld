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
    char errorMsg[80];
    int argc = lua_gettop(L);
    if (argc <= 1)
    {
        sprintf(errorMsg, "'addEventHandler' expected 2 arguments, only got %d", argc);
        lua_pushstring(L, errorMsg);
        lua_error(L);
        return 0;
    }

    int arg1 = lua_type(L, 1);
    int arg2 = lua_type(L, 2);

    if (lua_type(L, 1) != LUA_TSTRING)
    {
        sprintf(errorMsg, "'addEventHandler' expected string at argument 1, got %s instead", lua_typename(L, arg1));
        lua_pushstring(L, errorMsg);
        lua_error(L);
        return 0;
    }

    if (lua_type(L, 2) != LUA_TFUNCTION)
    {
        sprintf(errorMsg, "'addEventHandler' expected function at argument 2, got %s instead", lua_typename(L, arg2));
        lua_pushstring(L, errorMsg);
        lua_error(L);
        return 0;
    }

    const char *eventName = lua_tostring(L, 1);
    int handlerFnRef = luaL_ref(L, LUA_REGISTRYINDEX);
    addEventHandler(eventName, handlerFnRef);
    return 0;
}
