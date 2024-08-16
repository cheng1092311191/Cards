#include"pch.h"
#include"Server.h"



MyTcpListener::MyTcpListener()
{
}

MyTcpListener::~MyTcpListener()
{
}
EnHandleResult MyTcpListener::OnPrepareListen(ITcpServer* pSender, SOCKET soListen) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnHandShake(ITcpServer* pSender, CONNID dwConnID) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnShutdown(ITcpServer* pSender) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) { return HR_IGNORE; }





MyTcpListener g_Lister;

CTcpServerPtr g_hpTcp(&g_Lister);


