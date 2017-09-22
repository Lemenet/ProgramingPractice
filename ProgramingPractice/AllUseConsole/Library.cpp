#include "UsingDefine.h"

#ifdef _U_LIBRARY_

#include <iostream>
#include "../Library/MathLibrary.h"

#pragma comment(lib, "../Library/Lib/Library.lib")
int main(int argc, char** argv)
{

	int a = 100;
	int b = 200;
	std::cout << FMath::Max(a, b) << std::endl;

	getchar();
	return 0;
}


#endif // _ULIBRARY_
