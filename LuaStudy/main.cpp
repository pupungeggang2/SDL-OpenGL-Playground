#include <iostream>
#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char *argv[]) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    
}