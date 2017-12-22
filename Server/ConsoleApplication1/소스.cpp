#include "winsock2.h"

void main(void)
{
	WSADATA wsaData;

	SOCKET ListeningSocket;
	SOCKET NewConnection;
	SOCKADDR_IN ServerAddr;
	SOCKADDR_IN ClientAddr;
	int port = 5150;
	//���� ���� 2.2 �ʱ�ȭ
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Ŭ���̾�Ʈ ��û�� ���� ���� ����
	ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//SOCKADDR_IN ����ü ����, ��Ʈ ��ȣ 5150�� ���� ��� �������̽��� ���� ��û�� ���ε� ��Ű�� ���ؼ�
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//������ ���� ���ε�
	bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));

	//���ε� ��Ų ������ ������ ���¿� ���� , 5���� ����ڱ��� ����
	listen(ListeningSocket, 5);

	//��û�� �����ϸ� ����
	NewConnection = accept(ListeningSocket, (SOCKADDR *)&ClientAddr, &ClientAddrLen);

	//Ŭ��¡
	closesocket(NewConnection);
	closesocket(ListeningSocket);

	//��� ������ ������ WSACleanup ȣ��
	WSACleanup();
}


	