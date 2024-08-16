#pragma once

#include<HPSocket/HPSocket.h>



#ifdef _WIN64

	#ifdef _UNICODE
		#ifdef DEBUG
		#pragma comment(lib,"HPSocket/x64/HPSocket_UD.lib")
		#else
		#pragma comment(lib,"HPSocket/x64/HPSocket_U.lib")
		#endif // DEBUG


	#else
		#ifdef DEBUG
		#pragma comment(lib,"HPSocket/x64/HPSocket_D.lib")
		#else
		#pragma comment(lib,"HPSocket/x64/HPSocket.lib")
		#endif // DEBUG

	
	#endif // UNICODE



#else
	
	#ifdef _UNICODE

		#ifdef DEBUG
		#pragma comment(lib,"HPSocket/x32/HPSocket_UD.lib")
		#else
		#pragma comment(lib,"HPSocket/x32/HPSocket_U.lib")
		#endif // DEBUG


	#else
		#ifdef DEBUG
		#pragma comment(lib,"HPSocket/x32/HPSocket_D.lib")
		#else
		#pragma comment(lib,"HPSocket/x32/HPSocket.lib")
		#endif // DEBUG


	#endif // UNICODE



#endif // WIN64



class MyTcpListener:public CTcpServerListener
{
public:
	MyTcpListener();
	~MyTcpListener();

	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient);
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);

private:

};





extern CTcpServerPtr g_hpTcp;