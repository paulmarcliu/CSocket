// CBaseSocket.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include<winsock2.h>
#include "typedefs.h"
#include "CUdpSocket.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

//One UDP Rx and Tx Socket
int CUdpSocket::CreateSocket(void){
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
		return WSAGetLastError();
	}
	SOCKET s = socket(AF_INET , SOCK_DGRAM , 0 );
	if (s == INVALID_SOCKET){
		return WSAGetLastError();
	}
	else{
		CBaseSocket::Set(s);
	}
	return SUCCESS_OK;
}

int CUdpSocket::CloseSocket(void){
	closesocket(CBaseSocket::Get());
	WSACleanup();
	return SUCCESS_OK;
}

int CUdpSocket::BindSocket(void){
	if (bind(CBaseSocket::Get() ,(struct sockaddr *)&source_address , sizeof(source_address))== SOCKET_ERROR){
		CloseSocket();
		return WSAGetLastError();
	}
	unsigned long int nonBlockingMode = 1;
	ioctlsocket(CBaseSocket::Get(), FIONBIO, &nonBlockingMode);
	return SUCCESS_OK;
}

int CUdpSocket::Send(UINT8 *ptxBuf, UINT32 max_buffer_size, UINT32 txBufLen){
	int len = sizeof(destination_address);
	if (sendto(CBaseSocket::Get(), (const char *) ptxBuf, txBufLen, 0, (struct sockaddr*) &destination_address, len) == SOCKET_ERROR){
		CloseSocket();
		return WSAGetLastError();
	}
	return SUCCESS_OK;
}
int CUdpSocket::Receive(UINT8 *pRxBuf, UINT32 max_buffer_size, UINT32 *pRxBufLen){
	int len = sizeof(source_address);
	if ((*pRxBufLen = recvfrom(CBaseSocket::Get(), (char *) pRxBuf, max_buffer_size, 0, (struct sockaddr *) &source_address, &len)) == SOCKET_ERROR){
		return WSAGetLastError();
	}
	return SUCCESS_OK;
}



