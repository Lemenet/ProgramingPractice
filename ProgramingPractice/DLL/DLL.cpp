// DLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


extern "C" __declspec(dllexport)
float AddF(float a, float b)
{
	return a + b;
}