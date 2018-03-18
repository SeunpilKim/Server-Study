
#include "stdio.h"
#include "conio.h"
#include "winsock2.h"




//에러출력함수
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);

	exit(1);
}

int main()
{
	WSADATA wsaData;
	SOCKET hSocket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN recvAddr;
	WSAEVENT event = WSACreateEvent();
	WSAOVERLAPPED overlapped;

	char key;
	int flags = 0;
	int sendBytes = 0;
	int recvBytes = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");


	memset(&recvAddr, 0, sizeof(recvAddr));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	recvAddr.sin_port = htons(2738);

	if (connect(hSocket, (SOCKADDR*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");




	memset(&overlapped, 0, sizeof(overlapped));

	overlapped.hEvent = event;

	while (true)
	{
		flags = 0;
		

		WSABUF dataBuf;
		char message[1024] = { 0, };
		char userInfo[1031] = { "유저1:", };

		//scanf("%s", message);
		//fgets(message, 100, stdin);
		//strcat(userInfo, message);

		


		if (!strcmp(userInfo, "exit")) break;


	if (key != '\0') {
		
			dataBuf.len = 1;
			dataBuf.buf = "W";

			if (WSASend(hSocket, &dataBuf, 1, (LPDWORD)&sendBytes, 0, &overlapped, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
					ErrorHandling("WSASend() error");
			}

			WSAWaitForMultipleEvents(1, &event, TRUE, WSA_INFINITE, FALSE);

			WSAGetOverlappedResult(hSocket, &overlapped, (LPDWORD)&sendBytes, FALSE, NULL);

			//printf("전송된바이트수: %d \n", sendBytes);

			if (WSARecv(hSocket, &dataBuf, 1, (LPDWORD)&recvBytes, (LPDWORD)&flags, &overlapped, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
					ErrorHandling("WSASend() error");
			}

			printf("Recv[%s]\n", dataBuf.buf);
		}
	}
	

	return 0;
}



