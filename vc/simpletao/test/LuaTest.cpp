//Walter learn Lua , refer to http://csl.name/lua/
#include <iostream>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <stdint.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;

class CLuaState
{  
public:
  CLuaState() : L(luaL_newstate()) 
  { 
	  luaL_openlibs(L);
	  initialize();
  }

  ~CLuaState() {
      lua_close(L);
  }

  lua_State* GetLuaState() {return L; }

  int Execute(const char* szFile) {
	return luaL_dofile(L, szFile);
  }

  std::string GetError(int status) {
      std::string strError;
      if ( status!=0 ) {
          strError = lua_tostring(L, -1);;
          lua_pop(L, 1); // remove error message
      } else {
          return "OK";
      }
  }
  //lua_register(L, "my_function", my_function);
  // implicitly act as a lua_State pointer
  inline operator lua_State*() {
    return L;
  }

  int initialize();
private:
	lua_State *L;

};

static int drawText(lua_State* luaState)
{
	float screenPosY = (float) lua_tonumber(luaState, -1);		// get the value 160
	float screenPosX = (float) lua_tonumber(luaState, -2);		// get the value 240
	const char* str = lua_tostring(luaState, -3);				// get the value "Ready Go~"
	printf("Text '%s' draw at (%f, %f)\n", str, screenPosX, screenPosY);

	int textWidth= strlen(str);
	lua_pushnumber(luaState, textWidth);			// return a value to Lua
	return 1;									// number of values return to Lua
}

int CLuaState::initialize()
{
	
	return 0;
}

TEST(LuaTest, ExecuteFileTest)
{
	const char* szFile = "../../lua/insert_sort.lua";
	CLuaState oLState;

	int s = oLState.Execute(szFile);
	ASSERT_EQ(s, 0);
	
}


TEST(LuaTest, SimpleSample)
{
    int status, result, i;
    double sum;
    lua_State *L;

    /*
     * All Lua contexts are held in this structure. We work with it almost
     * all the time.
     */
    L = luaL_newstate();

    luaL_openlibs(L); /* Load Lua libraries */

    /* Load the file containing the script we are going to run */
    status = luaL_loadfile(L, "../../lua/script.lua");
    if (status) {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    /*
     * Ok, now here we go: We pass data to the lua script on the stack.
     * That is, we first have to prepare Lua's virtual stack the way we
     * want the script to receive it, then ask Lua to run it.
     */
    lua_newtable(L);    /* We will pass a table */

    /*
     * To put values into the table, we first push the index, then the
     * value, and then call lua_rawset() with the index of the table in the
     * stack. Let's see why it's -3: In Lua, the value -1 always refers to
     * the top of the stack. When you create the table with lua_newtable(),
     * the table gets pushed into the top of the stack. When you push the
     * index and then the cell value, the stack looks like:
     *
     * <- [stack bottom] -- table, index, value [top]
     *
     * So the -1 will refer to the cell value, thus -3 is used to refer to
     * the table itself. Note that lua_rawset() pops the two last elements
     * of the stack, so that after it has been called, the table is at the
     * top of the stack.
     */
    for (i = 1; i <= 5; i++) {
        lua_pushnumber(L, i);   /* Push the table index */
        lua_pushnumber(L, i*2); /* Push the cell value */
        lua_rawset(L, -3);      /* Stores the pair in the table */
    }

    /* By what name is the script going to reference our table? */
    lua_setglobal(L, "foo");

    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    /* Get the returned value at the top of the stack (index -1) */
    sum = lua_tonumber(L, -1);

    printf("Script returned: %.0f\n", sum);

    lua_pop(L, 1);  /* Take the returned value out of the stack */
    lua_close(L);   /* Cya, Lua */


}

TEST(LuaTest, HelloWorld)
{
	lua_State* L = luaL_newstate(); 
	luaL_openlibs(L); 

	lua_pushcfunction(L, drawText);
	lua_setglobal(L, "drawText");

	string strLuaCodes 
		= "local w = drawText('Ready Go~',  240, 160)\n"
		  "print('w=' ..w)";

	int error = luaL_loadstring(L, strLuaCodes.c_str());
    error = lua_pcall(L, 0, 0, 0);
	if (error) {
		fprintf(stderr, "error: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	lua_close(L);

}