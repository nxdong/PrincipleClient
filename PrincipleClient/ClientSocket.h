#include <MSWSock.h>
#include "Buffer.h"

class CClientSocket
{
private:
	// client socket of class. all recv,send is on this socket
	SOCKET	m_socket; 
	// handle to worker thread.
	HANDLE	m_hWorkerThread;
	// event.
	HANDLE	m_hEvent;
	// flag if the client is running.
	BOOL	m_bIsRunning;
	// store the flag . 'p' 'r' 'i' 'n'
	BYTE	m_bPacketFlag[4];
public:
	//
	CClientSocket();
	~CClientSocket();
	BOOL Connect(LPCTSTR ServerIP , UINT nPort);
	BOOL Disconnect();
	int	 Send(LPBYTE lpDate,UINT nSize);


};