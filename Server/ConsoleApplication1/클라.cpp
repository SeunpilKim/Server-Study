
#include "winsock2.h"

void main(void)
{
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN ServerAddr;
	int port = 5150;
	
	//������ ������ �� ���� ����
	int ret = 0;

	//���� 2.2 �ʱ�ȭ
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Ŭ���̾�Ʈ ������ ���ο� ���� ����
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���� ip�ּҸ� 136.149.3.29 ��� ����
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = inet_addr("136.149.3.29");

	//���ϰ� ���� ����
	connect(s, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));

	//������ ����, ����
	char sendbuff[2048];
	int nBytes = 2048, nLeft, idx;
	
	//sendbuff ä��� 

	//s�� ����� ��Ʈ�� �����̶�� ����
	nLeft = nBytes;
	idx = 0;

	while (nLeft > 0) {
		ret = send(s, &sendbuff[idx], nLeft, 0);
		if (ret == SOCKET_ERROR) {
			//���ۿ� ���� �߻�
		}
		nLeft -= ret;
		idx += ret;
	}

	//�پ� ���� Ŭ��¡
	closesocket(s);

	//������ ��� ���� �� WSACleanup ȣ��
	WSACleanup();
}

