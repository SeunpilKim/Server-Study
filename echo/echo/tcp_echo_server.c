#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUF_SIZE 1024                     // 메시지를 보낼 사이즈 매크로
void Error_handling(char* message);  // 에러함수 선언

int main(int argc, char* argv[])           // 메인함수 선언/정의부분
{

	WSADATA wsaData;
	SOCKET serv_sock, clnt_sock;          // 소켓변수(서버/클라이언트) 생성
	SOCKADDR_IN serv_addr, clnt_addr;  // 소켓주소를 담을 구조체 2개생성(서버/클라이언트)
	int i;

	int strLen;
	char message[BUF_SIZE];               // 메시지변수
	int clntAdrSize;

	if (argc != 2)
	{
		printf("Usage %s <port> \n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)  // 소켓프로그램 시작(버전 등록)
		Error_handling("WSAStartup() Error!");

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);   // 소켓생성(tcp등록)

	if (serv_sock == INVALID_SOCKET)
		Error_handling("socket() error");



	memset(&serv_addr, 0, sizeof(serv_addr));           // 메모리 초기화 /ip, 포트주소 할당
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));



	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) // 주소할당
		Error_handling("bind() error!");



	if (listen(serv_sock, 5) == SOCKET_ERROR)        // 수신된 소켓 저장
		Error_handling("listen() error!");



	clntAdrSize = sizeof(clnt_addr);                         // 소켓주소길이 저장



															 // printf("clnt_len = %d \n", clnt_len);

	for (i = 0; i<5; i++)
	{
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &clntAdrSize);  // 버퍼에  소켓 수신

																			 // accept(수신소켓, 소켓메모리할당주소, 소켓주소(번지)

		if (clnt_sock == -1)
			Error_handling("accept() error!");



		else
			printf("call from client : %d \n", i + 1);



		while ((strLen = recv(clnt_sock, message, BUF_SIZE, 0)) != 0)        // recv()리턴값은 message 길이
		{                // recv(받을주소, 메시지주소, 메시지크기, 0)
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
