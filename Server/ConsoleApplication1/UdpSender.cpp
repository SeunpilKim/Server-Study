#include <winsock2.h>

void main(void)
{
	WSADATA wsaData;
	SOCKET SendingSocket;
	SOCKADDR_IN ReceiveAddr;
	int port = 5150;
	char SendBuf[1024];
	int BufLength = 1024;

	//���� ���� 2.2 �ʱ�ȭ
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//���� ���� ����
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//Ŭ���̾�Ʈ�� �����ϰ�, ������ �ּҰ� ����, ip�ּҴ� 136.149.3.29 ��� ����
	ReceiveAddr.sin_family = AF_INET;
	ReceiveAddr.sin_port = htons(port);
	ReceiveAddr.sin_addr.s_addr = inet_addr("136.149.3.29");

	//���ù� ���Ͽ� �ڷ� ����
	sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&ReceiveAddr, sizeof(ReceiveAddr));

	closesocket(SendingSocket);

	WSACleanup();
}