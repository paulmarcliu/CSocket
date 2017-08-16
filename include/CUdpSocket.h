#ifndef __CUDPSOCKET_H__
#define __CUDPSOCKET_H__

#include <winsock2.h>
#include "CBaseSocket.h"

//One UDP Rx and Tx Socket
class CUdpSocket : public CBaseSocket
{
public:
	CUdpSocket(){}
	~CUdpSocket(){}

	virtual int CreateSocket(void);
	virtual int CloseSocket(void);
	virtual int BindSocket(void);
	virtual int Send(UINT8 *tx_buf, UINT32 max_buffer_size, UINT32 buf_len);
	virtual int Receive(UINT8 *rx_buf, UINT32 max_buffer_size, UINT32 *buf_len);

	/** Only applicable to UDP / TCP */
	void ConfigureSourceSocket(char *ip, UINT32 port){
		memset(&source_address, 0, sizeof(source_address));
		source_address.sin_family = AF_INET;
		source_address.sin_port = htons(port);
		source_address.sin_addr.s_addr = inet_addr(ip);
	}

	void ConfigureDestinationSocket(char *ip, UINT32 port){
		memset(&destination_address, 0, sizeof(destination_address));
		destination_address.sin_family = AF_INET;
		destination_address.sin_port = htons(port);
		destination_address.sin_addr.s_addr = inet_addr(ip);
	}
private:
	struct sockaddr_in destination_address;	
	struct sockaddr_in source_address;
};





#endif // __CUDPSOCKET_H__