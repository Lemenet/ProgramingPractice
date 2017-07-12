#include <thread>
#include <iostream>
#include <string>
#include <windows.h>



void CallBack1(int n)
{
	for (int i = 0; i < n; ++i)
	{
		Sleep(100);
		std::cout << "1One " << i << std::endl;
	}
	/*char a[10];
	std::cin >> a;
	printf("thread 1 %s", a);*/
}

void CallBack2(int* n)
{
	*n = 40;
	for (int i = 0; i < 10; ++i)
	{
		Sleep(100);
		//std::cout << "2Two " << i << std::endl;
		*n += 1;
		std::cout << *n << std::endl;
	}
	/*char a[10];
	std::cin >> a;
	printf("thread 2 %s", a);;*/
}


int main(int argc, char** argv)
{
	int* n = new int(0);
	std::cout << "Main thread running!!!" << std::endl;
	std::thread t1(CallBack1, 30);
	std::thread t2(CallBack2, n);
	t2.join();
	std::cout << "Main" << *n << std::endl;
	//Sleep(3000);
	for (int i = 0; i < 10; ++i)
	{
		Sleep(100);
		std::cout << "Main " << i << std::endl;
	}
	
	
	t1.join();

	std::cout << "Main thread ending!!!" << std::endl;

	getchar();
	getchar();
	getchar();
	getchar();
	return 0;
}