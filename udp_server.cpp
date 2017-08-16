// CBaseSocket.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <winsock2.h>

#include "typedefs.h"
#include "CUdpSocket.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library


#define MAX_BUF_SIZE	1024


int _tmain(int argc, _TCHAR* argv[])
{
	UINT8 udp_tx_buf[MAX_BUF_SIZE];
	UINT8 udp_rx_buf[MAX_BUF_SIZE];
	int return_value;
	UINT32 bytes_read;
	int counter;
    CUdpSocket k;
	k.ConfigureSourceSocket("127.0.0.1", 1001);
	k.ConfigureDestinationSocket("127.0.0.1", 1002);
	return_value = k.CreateSocket();
	if (return_value != SUCCESS_OK){
		std::cout << "Error creating socket : " << return_value << std::endl;
	}

	return_value = k.BindSocket();		// Bind the server
	if (return_value != SUCCESS_OK){
		std::cout << "Cannot bind socket : " << return_value << std::endl;
	}
	k.SetState(STATE_RUN);
	counter = 0;
	while (k.GetState() == STATE_RUN){
		if (k.Receive(&udp_rx_buf[0], MAX_BUF_SIZE, &bytes_read) == SUCCESS_OK){
			if (bytes_read > 0){
				memcpy(&udp_tx_buf[0], &udp_rx_buf[0], bytes_read);
				k.Send(&udp_tx_buf[0], MAX_BUF_SIZE, bytes_read);
				std::cout << counter++ << ":Rx " << bytes_read << std::endl;
			}
		}
	}
	return 0;
}
