
#include <iostream>

using namespace std;
#pragma once

// ���� ���� �Լ�.
//
/////////////////////////////////////////////////////////////////////
#ifndef __SERVER_MAIN__
#define __SERVER_MAIN__

#define BUFSIZE 1024

char* timeToString(struct tm *t);

int SessionID = 0;

typedef struct
{
	SOCKET hClntSock;
	SOCKADDR_IN clntAddr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsaBuf;
} PER_IO_DATA, *LPPER_IO_DATA;

#pragma comment(lib, "ws2_32.lib")

/////////////////////////////////////////////////////////////////////
// �����ʱ�ȭ.
//
// Parameters: ����.
// Return: ����.
/////////////////////////////////////////////////////////////////////
BOOL InitServer(void);

/////////////////////////////////////////////////////////////////////
// ��������.
//
// Parameters: ����.
// Return: ����.
/////////////////////////////////////////////////////////////////////
BOOL ReleaseServer(void);

/////////////////////////////////////////////////////////////////////
// ���� �Լ�.
//
// Parameters: ����.
// Return: ����.
/////////////////////////////////////////////////////////////////////
void main(void);


void ErrorHandling(char *message);

unsigned int __stdcall CompletionThread(LPVOID pComPort);

#endif