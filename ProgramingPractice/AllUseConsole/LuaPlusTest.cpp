#include "UsingDefine.h"

#ifdef _U_LUAPLUS_TEST_

#include <iostream>
#include "LuaPlus.h"

using namespace LuaPlus;
using namespace std;


int PrintNumber(LuaState* state)
{
	LuaStack args(state);
	if (args[1].IsNumber())
	{
		cout << args[1].GetNumber() << endl;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	LuaStateOwner state;

	//当需要向lua脚本中注册C++函数时，一定要在执行脚本之前进行注册
	//如果注册之前调用，则会DoFile失败
	state->GetGlobals().Register("C_PrintNumber", PrintNumber);

	int iret = state->DoFile("test.lua");

	if (iret)
	{
		std::cout << "Lua DoFile 失败" << std::endl;

		system("pause");
		return 0;
	}

	//int myHealth = state->GetGlobal("health").GetInteger();
	int myHealth = state->GetGlobals()["health"].GetInteger();

	cout << myHealth << endl;

	LuaFunction<float> CAdd = state->GetGlobal("Add");

	//用C++调用Lua函数时
	//如果C++这边参数如果过多，Lua函数仍然可以调用，但是多余参数会被舍弃
	//如果C++这边参数过少，则会引起函数调用时的崩溃
	cout << CAdd(3.4f, 4.2f, 4.4f) << endl;
	cout << CAdd(3.4f,1.f) << endl;


	system("pause");
	return 0;
}



#endif // !_ULUATEST_
