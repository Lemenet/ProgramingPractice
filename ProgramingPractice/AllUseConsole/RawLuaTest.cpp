#include "UsingDefine.h"

#ifdef _U_RAW_LUA_TEST_

#include <iostream>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
}


using namespace std;

int main(int argc, char* argv[])
{
	lua_State* state = luaL_newstate();

	if (state == NULL)
	{
		cout << "LuaState����ʧ��" << endl;
		system("pause");
		return 0;
	}

	int bRet = luaL_loadfile(state, "test.lua");
	if (bRet)
	{
		cout << "load file error" << endl;
		system("pause");
		return 0;
	}

	lua_pushfstring(state, "��push������string");
	cout << lua_tostring(state, -1) << endl;

	//bRet = lua_pcall(state, 0, 0, 0);
	//if (bRet)
	//{
	//	cout << "pcall error" << endl;
	//	system("pause");
	//	return 0;
	//}

	lua_getglobal(state, "health");
	long long int health = lua_tointeger(state, -1);
	cout << health << endl;







	system("pause");
	return 0;

}




















#endif // _U_RAW_LUA_TEST_
