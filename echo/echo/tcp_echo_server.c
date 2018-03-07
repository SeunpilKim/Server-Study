#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUF_SIZE 1024                     // �޽����� ���� ������ ��ũ��
void Error_handling(char* message);  // �����Լ� ����

int main(int argc, char* argv[])           // �����Լ� ����/���Ǻκ�
{

	WSADATA wsaData;
	SOCKET serv_sock, clnt_sock;          // ���Ϻ���(����/Ŭ���̾�Ʈ) ����
	SOCKADDR_IN serv_addr, clnt_addr;  // �����ּҸ� ���� ����ü 2������(����/Ŭ���̾�Ʈ)
	int i;

	int strLen;
	char message[BUF_SIZE];               // �޽�������
	int clntAdrSize;

	if (argc != 2)
	{
		printf("Usage %s <port> \n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)  // �������α׷� ����(���� ���)
		Error_handling("WSAStartup() Error!");

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);   // ���ϻ���(tcp���)

	if (serv_sock == INVALID_SOCKET)
		Error_handling("socket() error");



	memset(&serv_addr, 0, sizeof(serv_addr));           // �޸� �ʱ�ȭ /ip, ��Ʈ�ּ� �Ҵ�
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));



	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) // �ּ��Ҵ�
		Error_handling("bind() error!");



	if (listen(serv_sock, 5) == SOCKET_ERROR)        // ���ŵ� ���� ����
		Error_handling("listen() error!");



	clntAdrSize = sizeof(clnt_addr);                         // �����ּұ��� ����



															 // printf("clnt_len = %d \n", clnt_len);

	for (i = 0; i<5; i++)
	{
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &clntAdrSize);  // ���ۿ�  ���� ����

																			 // accept(���ż���, ���ϸ޸��Ҵ��ּ�, �����ּ�(����)

		if (clnt_sock == -1)
			Error_handling("accept() error!");



		else
			printf("call from client : %d \n", i + 1);



		while ((strLen = recv(clnt_sock, message, BUF_SIZE, 0)) != 0)        // recv()���ϰ��� message ����
		{                // recv(�����ּ�, �޽����ּ�, �޽���ũ��, 0)
			printf("recv_len = %d \n", strLen);
			send(clnt_sock, message, strLen, 0);
		}

		closesocket(clnt_sock);
	}

	closesocket(serv_sock);
	WSACleanup();
	return 0;
}

void Error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
