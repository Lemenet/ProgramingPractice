/************************************************************************/
//
//	作者：黄梦迪
//
//	时间：2017/07/14
//
//	功能描述：网上找到的普通的Windows网络连接
//			这一部分是服务器端，用基本的socket套接字通信完成网络通信
//			
/************************************************************************/

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")


int main(int argc, char** argv)
{
	WSADATA wsaData;
	int port = 888;
	char buff[] = "Server: Hello, I am a server.....";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock");
		return 0;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR)
	{
		printf("Listen failed :%d", WSAGetLastError());
		return 0;
	}

	if (listen(sockSrv, 10) == SOCKET_ERROR)
	{
		printf("Listen failed:%d", WSAGetLastError());
		return 0;
	}

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (true)
	{
		SOCKET sockConnect = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		if (sockConnect == SOCKET_ERROR)
		{
			printf("Accept failed:%d", WSAGetLastError());
			break;
		}

		printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));

		int iSend = send(sockConnect, buff, sizeof(buff), 0);
		if (iSend == SOCKET_ERROR)
		{
			printf("send failed");
			break;
		}

		char recvBuff[100];
		memset(recvBuff, 0, sizeof(recvBuff));

		recv(sockConnect, recvBuff, sizeof(recvBuff), 0);
		printf("%s\n", recvBuff);


		closesocket(sockConnect);

	}

	closesocket(sockSrv);
	WSACleanup();
	system("pause");

	return 0;
}