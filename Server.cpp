#include"pch.h"
#include"Server.h"
#include"resource.h"

EnHandleResult on_card_notice(ITcpServer* pSender, CONNID dwConnID)
{

	int size = 0;
	CWnd* pWnd = ::AfxGetApp()->GetMainWnd();
	char buf[1024] = { 0 };
	int len = pWnd->GetDlgItemTextA(IDC_EDIT_NOTICE, buf, 1024);
	len = strlen(buf);
	int bobySize = len + 1;
	size = sizeof(PACK_HEADER_T) + bobySize;
	PPACK_T pResPack = (PPACK_T)SYS_Malloc(size);
	if (pResPack == nullptr)
	{

		return HR_ERROR;
	}
	memset(pResPack, 0, size);
	//构建包头
	pResPack->Hdr.sType = card_notice;
	pResPack->Hdr.nPackSize = size;
	pResPack->Hdr.nBobySize = bobySize;
	//拷贝包体
	memcpy(&pResPack->Boby, buf, bobySize);

	pSender->Send(dwConnID, (LPBYTE)pResPack, size);
	//delete pResPack;
	SYS_Free((LPBYTE) pResPack);

	return HR_IGNORE;
}


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
EnHandleResult MyTcpListener::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	CWnd* wnd =  ::AfxGetApp()->GetMainWnd();
	if (!(wnd&& wnd->GetSafeHwnd()))
	{
		goto _ret;
	}
	PPACK_T pPack = (PPACK_T)pData;

	

	switch (pPack->Hdr.sType)
	{
	case card_keep_alive:
		break;
	case card_notice:
		return on_card_notice(pSender, dwConnID);
		break;
	case card_look:
		break;
	case card_verify:
		break;
	case card_exit:
		break;
	default:
		break;
	}


_ret:
	return HR_IGNORE; 
}
EnHandleResult MyTcpListener::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnShutdown(ITcpServer* pSender) { return HR_IGNORE; }
EnHandleResult MyTcpListener::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) { return HR_IGNORE; }





MyTcpListener g_Lister;

CTcpServerPtr g_hpTcp(&g_Lister);


