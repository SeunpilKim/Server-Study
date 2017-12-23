#include <winsock2.h>

void main(void)
{
	WSADATA wsaData;
	SOCKET ReceivingSocket;

	SOCKADDR_IN ReceiverAddr;
	int port = 5150;

	char ReceiveBuf[1024];
	int BufLength = 1024;
	SOCKADDR_IN SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);

	//���� ���� 2.2 �ʱ�ȭ
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//���� ���� ����
	ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//���� ���� �ּ� ���ε�
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(port);
	ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(ReceivingSocket, (SOCKADDR *)&SenderAddr, sizeof(SenderAddr));

	//�޴� �۾� ó��
	recvfrom(ReceivingSocket, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);

	//�޴°� �Ϸ�Ǹ� ������ �ݴ´�.
	closesocket(ReceivingSocket);

	WSACleanup();
}