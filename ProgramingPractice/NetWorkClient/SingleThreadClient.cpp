/************************************************************************/
//
//	���ߣ����ε�
//
//	ʱ�䣺2017/07/14
//
//	���������������ҵ�����ͨ��Windows��������
//			��һ�����ǿͻ��ˣ��û�����socket�׽���ͨ���������ͨ��
//			ԭ��׼����C������ɣ������ڴ���������ʱ̫�鷳�����Ի���������STL��string�ļ�
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
	//�����׽���
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

	//�����׽���  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient)
	{
		printf("Socket() error:%d", WSAGetLastError());
		return 0;;
	}

	//�������������������  
	if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		printf("Connect failed:%d", WSAGetLastError());
		return 0;;
	}
	else
	{
		//��������  
		recv(sockClient, buff, sizeof(buff), 0);
		printf("%s\n", buff);
	}

	//��������  
	std::string strBuf = "hello, this is a Client....";
	memcpy(buff, strBuf.c_str(), strBuf.length());
	send(sockClient, buff, sizeof(buff), 0);

	//�ر��׽���  
	closesocket(sockClient);
	WSACleanup();


	system("pause");
	return 0;

}
#endif // U_SingleThreadNetWork