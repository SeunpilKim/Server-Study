#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024

void Error_handling(char* message);

int main(int argc, char *argv[])
{

	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN sock_addr;
	char message[BUF_SIZE];
	int strLen;

	if (argc != 3)
	{
		printf("Usage %s <ip> <port> \n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error_handling("WSAStartup() error!");

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
		Error_handling("socket() error!");


	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
	sock_addr.sin_port = htons(atoi(argv[2]));



	if (connect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR)
		Error_handling("connect() error");



	else
		printf("connected ............ (server)\n");


	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) // q/Q를 누르면 종료
			break;

		send(sock, message, strlen(message), 0);
		strLen = recv(sock, message, BUF_SIZE - 1, 0);

		message[strLen] = 0;
		printf("server from message : %s \n", message);

	}

	closesocket(sock);
	WSACleanup();
	return 0;
}

void Error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
