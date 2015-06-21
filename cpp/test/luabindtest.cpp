extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaUtil.h"
#include <string>
#include <iostream>
#include <luabind/luabind.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/copy_policy.hpp>
#include <luabind/adopt_policy.hpp>

using namespace std;
using namespace luabind;

enum CommandResult {
        COMMAND_RESULT_OK = 0,
        COMMAND_RESULT_FAILURE,
        COMMAND_RESULT_INPROGRESS
};


enum CommandType {
		COMMAND_ADD = 0,
		COMMAND_REMOVE,
		COMMAND_UPDATE
};

class CCommandExecutor
{
public:
    object& Execute(CommandType cmdType, object const& table, lua_State* pL)
    {
        cout<<"cmdType="<<cmdType<<endl;
        luabind::object tblRet = newtable(pL);
        if(type(table) == LUA_TTABLE)
        {
            tblRet["result"] = COMMAND_RESULT_OK;

        }
        return tblRet;
    }
};

class CLuaEnum
{
};

void LuaBindEnum(lua_State* L) 
{
	module(L)
	[
	    class_<CCommandExecutor>("CommandExecutor")
	        .def("Execute", &CCommandExecutor::Execute),

		class_<CLuaEnum>("CLuaEnum")
			.enum_("CommandResult")
		[
			value("COMMAND_RESULT_OK", COMMAND_RESULT_OK),
			value("COMMAND_RESULT_FAILURE", COMMAND_RESULT_FAILURE),
			value("COMMAND_RESULT_INPROGRESS", COMMAND_RESULT_INPROGRESS)
		]
        .def(constructor<>()) 
	];
}
int main(int argc, char* argv[])
{
	string strLuaCodes = "print (CLuaEnum.COMMAND_RESULT_FAILURE .. ', ' ..CLuaEnum.COMMAND_RESULT_INPROGRESS)";
	CLuaUtil aLuaUtil;
	lua_State* pL = aLuaUtil.GetLuaState();
	if(NULL == pL) return -1;
   
	LuaBindEnum(pL);   
	aLuaUtil.ExecuteLuaCodes(strLuaCodes.c_str());
    aLuaUtil.ExecuteLuaCodes("print(CLuaEnum)");
	return 0;
}
/*
--- output ---
1, 2
userdata: 0x2238b18


*/

