#ifndef __CBASESOCKET_H__
#define __CBASESOCKET_H__
/**
Comments will be added later on when using CLion
*/
#include "typedefs.h"

class CBaseSocket
{
public:
	CBaseSocket(){
		s = 0;	// descriptor
		socket_state = STATE_INIT;
	}
    virtual ~CBaseSocket() { /* ... */ }

	virtual int CreateSocket(void)= 0;
	virtual int CloseSocket(void)=0;
	virtual int BindSocket(void)=0;
	virtual int Send(UINT8 *tx_buf, UINT32 max_buffer_size, UINT32 buf_len)=0;
	virtual int Receive(UINT8 *rx_buf, UINT32 max_buffer_size, UINT32 *buf_len)=0;

	/**
	Socket
	*/
    void Set(SOCKET value){s = value;}
    SOCKET Get(void) const{return s;}

	/**
	State
	*/
	void SetState(RUN_STATE state){socket_state = state;}
	RUN_STATE GetState(void) const {return socket_state;}
	/**
	Buffer
	*/
private:
	SOCKET s;	// descriptor
	RUN_STATE	socket_state;
};

#endif	// __CBASESOCKET_H__