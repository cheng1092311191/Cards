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



enum pack_type
{
	card_keep_alive	=	0xCFAC,



	//公告
	card_notice,
	//卡密操作
	card_look = 0xEB90,
	//验证
	card_verify,
	//
	card_exit,

};

#pragma pack(1)
struct Pack_Header_t
{
	//保留, 值无效
	USHORT reserve;
	USHORT sType;
	uint32_t nPackSize;
	uint32_t nBobySize;

};
struct Pack_t
{
	Pack_Header_t Hdr;
	BYTE Boby[1];

};
#pragma pack()
typedef Pack_Header_t PACK_HEADER_T ,*PPACK_HEADER_T;
typedef Pack_t PACK_T,*PPACK_T;

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