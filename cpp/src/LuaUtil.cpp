#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream> 
#include <luabind/luabind.hpp>
#include "LuaUtil.h"

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

using namespace std;
using namespace luabind;

CLuaUtil::CLuaUtil()
: m_pState(NULL),m_bInited(false)
{
    Init();
    m_strLuaPath = GetLuaPath();
}

string CLuaUtil::GetLuaPath()
 {
    string path = "../../lua/?.lua;";
    if (NULL != getenv("LUA_PATH")) {
        path = getenv("LUA_PATH");
        path = path + "/?.lua";
    } 
    return path;
}

CLuaUtil::~CLuaUtil()
{
    Clean();
}

std::string CLuaUtil::GetString(std::string strKeyword, std::string strCaseName)
{
    return ReadTestData(strKeyword, strCaseName);
}

int CLuaUtil::GetNumber(std::string strKeyword, std::string strCaseName)
{
    return atoi(ReadTestData(strKeyword, strCaseName).c_str());
}

std::string CLuaUtil::ReadTestData(std::string strKeyword, std::string strCaseName)
{
    string strItem = strKeyword ;
    if(!strCaseName.empty()) {
        strItem = strCaseName;
    }
    lua_getglobal(m_pState, strItem.c_str());

    if (lua_isstring (m_pState, -1))
    {
        const char* pValue = lua_tostring(m_pState, -1);
		lua_pop(m_pState,-1);
        string strValue = pValue? pValue:"";
        return strValue;
    }
    else if(lua_isnumber (m_pState, -1))
    {
        double dValue = lua_tonumber(m_pState, -1);
		lua_pop(m_pState,-1);
        string strRet = "";
        stringstream ss;
        ss << dValue;
        ss >> strRet;
        return strRet;
    }
    else if(lua_istable (m_pState, -1) && !strCaseName.empty())
    {
        lua_getfield(m_pState, -1, strKeyword.c_str());
        if (lua_isstring (m_pState, -1)) {
            const char* pValue = lua_tostring(m_pState, -1);
			lua_pop(m_pState,-1);
            string strValue = pValue? pValue:"";
            return strValue;
        }
    }

    cerr << strItem <<" should be a valid string, number or table" << endl;
    return "";

}

int CLuaUtil::ExecuteLuaFile(std::string strLuaFile)
{

    //string strLuaFile = m_strLuaPath + TEST_DATA_PATH + strFileName;
    int nRet = LoadLuaFile(m_pState, strLuaFile.c_str());
    if(0 != nRet) {
        cerr<<strLuaFile<<" not exist\n" <<endl;
    }
    return nRet;
}



int CLuaUtil::ExecuteLuaCodes(string strLuaCodes) {
    int error = luaL_loadstring(m_pState, strLuaCodes.c_str())
            || lua_pcall(m_pState, 0, 0, 0);
    if (error) {
        fprintf(stderr, "%s", lua_tostring(m_pState, -1));
        lua_pop(m_pState, 1);
    }
    return error;
}

int CLuaUtil::LoadLuaFile(lua_State *pState, const char* pFileName)
{
    int nRet = 0;
    if (NULL == pState) {
        printf("[LoadLuaFile]pState is NULL./n");
        return -1;
    }
    cout<<"Load " << pFileName << ", pState=" << pState << endl;
    nRet = luaL_dofile(pState, pFileName);
    if (nRet != 0) {
        printf("[LoadLuaFile]luaL_loadfile(%s) is file(%d)(%s)./n",
                pFileName, nRet, lua_tostring(pState, -1));
        return -1;
    }

    return nRet;
}

void CLuaUtil::Init()
{
    m_pState = luaL_newstate();
    luaL_openlibs(m_pState);
    //luabind open
	open(m_pState);
}

void CLuaUtil::Clean()
{
    lua_close(m_pState);
}

void CLuaUtil::Reset()
{
    this->Clean();
    this->Init();
}
