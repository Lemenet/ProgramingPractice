#include "UsingDefine.h"

#ifdef _U_DLL_

#include <WinBase.h>
#include <tchar.h>
#include <stdio.h>

extern "C" __declspec(dllimport)
float Addf(float a, float b);

int main(int argc, char* argv[])
{

	HMODULE dll = LoadLibrary(_T("DLL.dll"));


	printf("%d", Addf(1.f, 2.3));



	getchar();
	return 0;
}

#endif // _UDLL_
