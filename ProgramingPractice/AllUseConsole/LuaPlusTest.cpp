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

	//����Ҫ��lua�ű���ע��C++����ʱ��һ��Ҫ��ִ�нű�֮ǰ����ע��
	//���ע��֮ǰ���ã����DoFileʧ��
	state->GetGlobals().Register("C_PrintNumber", PrintNumber);

	int iret = state->DoFile("test.lua");

	if (iret)
	{
		std::cout << "Lua DoFile ʧ��" << std::endl;

		system("pause");
		return 0;
	}

	//int myHealth = state->GetGlobal("health").GetInteger();
	int myHealth = state->GetGlobals()["health"].GetInteger();

	cout << myHealth << endl;

	LuaFunction<float> CAdd = state->GetGlobal("Add");

	//��C++����Lua����ʱ
	//���C++��߲���������࣬Lua������Ȼ���Ե��ã����Ƕ�������ᱻ����
	//���C++��߲������٣��������������ʱ�ı���
	cout << CAdd(3.4f, 4.2f, 4.4f) << endl;
	cout << CAdd(3.4f,1.f) << endl;


	system("pause");
	return 0;
}



#endif // !_ULUATEST_
