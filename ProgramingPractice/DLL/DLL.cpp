// DLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"


extern "C" __declspec(dllexport)
float AddF(float a, float b)
{
	return a + b;
}