#include "UsingDefine.h"

#ifdef _U_RAW_LUA_TEST_

#include <iostream>

//����Lua��Lib���Ǵ�C��Ŀ������һ��Ҫ����extern "C"�������У�������޷������ⲿ����
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace std;


void OutputLuaStack(lua_State* state)
{
	cout << "=====ջ��===== " << lua_gettop(state) << endl;
	for (int i = 1; i <= lua_gettop(state); ++i)
	{
		if (lua_isstring(state, -i))
		{
			cout << luaL_typename(state, -i)<< "-> " << lua_tostring(state, -i) << endl;
		}
		else if (lua_isfunction(state, -i))
		{
			cout << luaL_typename(state, -i) << "-> " << endl;
		}
		else if (lua_isnumber(state, -i))
		{
			cout << luaL_typename(state, -i) << "-> " << lua_tointeger(state, -i) << endl;
		}
		else if (lua_istable(state, -i))
		{
			cout << luaL_typename(state, -i) << "-> " << endl;
		}
		else
		{
			cout << luaL_typename(state, -i) << "-> " << endl;
		}
	}
	cout << "=====ջ��=====" << endl << endl;
}



int main(int argc, char* argv[])
{
	string str;

	cout << "lua_State* state = luaL_newstate();" << endl;
	lua_State* state = luaL_newstate();

	if (state == NULL)
	{
		cout << "LuaState����ʧ��" << endl;
		system("pause");
		return 0;
	}
	OutputLuaStack(state);

	cout << "int bRet = luaL_loadfile(state, \"test2.lua\");" << endl;
	int bRet = luaL_loadfile(state, "test2.lua");
	if (bRet)
	{
		cout << "load file error" << endl;
		system("pause");
		return 0;
	}
	OutputLuaStack(state);

	//��luaL_loadfile�Ժ�ᵼ��һ���޲��޷��صĺ�����������pcallȥ
	cout << R"(bRet = lua_pcall(state, 0, 0, 0);)" << endl;
	bRet = lua_pcall(state, 0, 0, 0);
	if (bRet)
	{
		cout << "pcall error" << endl;
		system("pause");
		return 0;
	}
	OutputLuaStack(state);

	cout << "lua_pushstring(state, \"��push������string\");" << endl;
	lua_pushstring(state, "��push������string");
	OutputLuaStack(state);



	cout << "lua_newtable(state);" << endl;
	lua_newtable(state);
	OutputLuaStack(state);





	cout << "lua_getglobal(state, \"tbl\");" << endl;
	lua_getglobal(state, "tbl");
	OutputLuaStack(state);

	cout << "lua_getfield(state, -1, \"name\");" << endl;
	lua_getfield(state, -1, "name");
	OutputLuaStack(state);



	cout << "lua_pushstring(state, \"�µ�new string\");" << endl;
	lua_pushstring(state, "�µ�new string");
	OutputLuaStack(state);

	cout << R"(lua_setfield(state, 3, "name");)" << endl;
	lua_setfield(state, 3, "name");
	OutputLuaStack(state);

	cout << R"(lua_getfield(state, 3, "name");)" << endl;
	lua_getfield(state, 3, "name");
	OutputLuaStack(state);

	cout << R"(lua_getglobal(state, "add");)" << endl;
	lua_getglobal(state, "add");
	OutputLuaStack(state);

	cout << R"(lua_pushinteger(state, 12);)" << endl;
	lua_pushinteger(state, 12);
	OutputLuaStack(state);

	cout << R"(lua_pushinteger(state, 22);)" << endl;
	lua_pushinteger(state, 22);
	OutputLuaStack(state);


	cout << R"(lua_pcall(state, 2, 1, 0);)" << endl;
	lua_pcall(state, 2, 1, 0);
	OutputLuaStack(state);


	cout << lua_tointeger(state, -1) << endl;
	OutputLuaStack(state);

	system("pause");
	return 0;

}



/*
void main()
{
	//1.����Lua״̬  
	cout << "lua_State *L = luaL_newstate();" << endl;
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		return;
	}
	OutputLuaStack(L);

	//2.����Lua�ļ�  
	cout << "int bRet = luaL_loadfile(L, \"test2.lua\");" << endl;
	int bRet = luaL_loadfile(L, "test2.lua");
	if (bRet)
	{
		cout << "load file error" << endl;
		return;
	}
	OutputLuaStack(L);

	//3.����Lua�ļ�  
	cout << "bRet = lua_pcall(L, 0, 0, 0);" << endl;
	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet)
	{
		cout << "pcall error" << endl;
		return;
	}
	OutputLuaStack(L);

	//4.��ȡ����  
	cout << "lua_getglobal(L, \"str\");" << endl;
	lua_getglobal(L, "str");
	string str = lua_tostring(L, -1);
	cout << "str = " << str.c_str() << endl;        //str = I am so cool~  
	OutputLuaStack(L);
													//5.��ȡtable  
	cout << R"(lua_getglobal(L, "tbl");)" << endl;
	lua_getglobal(L, "tbl");
	OutputLuaStack(L);

	cout << R"(lua_getfield(L, -1, "name");)" << endl;
	lua_getfield(L, -1, "name");
	str = lua_tostring(L, -1);
	cout << "tbl:name = " << str.c_str() << endl; //tbl:name = shun  
	OutputLuaStack(L);

												  //6.��ȡ����  
	lua_getglobal(L, "add");        // ��ȡ������ѹ��ջ��  
	lua_pushnumber(L, 10);          // ѹ���һ������  
	lua_pushnumber(L, 20);          // ѹ��ڶ�������  
	int iRet = lua_pcall(L, 2, 1, 0);// ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  
	if (iRet)                       // ���ó���  
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		cout << pErrorMsg << endl;
		lua_close(L);
		return;
	}
	if (lua_isnumber(L, -1))        //ȡֵ���  
	{
		double fValue = lua_tonumber(L, -1);
		cout << "Result is " << fValue << endl;
	}

	OutputLuaStack(L);

	system("pause");
}

*/

















#endif // _U_RAW_LUA_TEST_
