/************************************************************************/
//
//	作者：黄梦迪
//
//	时间：2017/07/14
//
//	功能描述：网上找到的普通的Windows网络连接
//			这一部分是客户端，用基本的socket套接字通信完成网络通信
//			原本准备用C语言完成，但是在处理缓冲内容时太麻烦，所以还是引入了STL的string文件
//			
/************************************************************************/


#include "../SolutionDefineMacro.h"

#ifdef U_SingleThreadNetWork


#include <WinSock2.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char** argv)
{
	//加载套接字
	WSADATA wsaData;
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("failed to load winsock");
		return 0;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(888);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//创建套接字  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient)
	{
		printf("Socket() error:%d", WSAGetLastError());
		return 0;;
	}

	//向服务器发出连接请求  
	if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		printf("Connect failed:%d", WSAGetLastError());
		return 0;;
	}
	else
	{
		//接收数据  
		recv(sockClient, buff, sizeof(buff), 0);
		printf("%s\n", buff);
	}

	//发送数据  
	std::string strBuf = "hello, this is a Client....";
	memcpy(buff, strBuf.c_str(), strBuf.length());
	send(sockClient, buff, sizeof(buff), 0);

	//关闭套接字  
	closesocket(sockClient);
	WSACleanup();


	system("pause");
	return 0;

}
#endif // U_SingleThreadNetWork