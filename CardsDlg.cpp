// CardsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Cards.h"
#include "CardsDlg.h"
#include "afxdialogex.h"
#include"resource.h"

#include"help.h"
#include"HttpServer.h"
#include<string>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif







// CCardsDlg 对话框



CCardsDlg::CCardsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CARDS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}

BEGIN_MESSAGE_MAP(CCardsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CCardsDlg::OnSelchangeTab)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCardsDlg 消息处理程序

BOOL CCardsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	srand(time(NULL));

	AddPage(m_Tab, "在线管理", m_OnLinePage, IDD_DIALOG_PAGE_ONLINE);
	AddPage(m_Tab, "卡密管理",m_ManagePage,IDD_DIALOG_PAGE_MANAGE);
	AddPage(m_Tab, "卡密生成",m_MakePage,IDD_DIALOG_PAGE_MAKE);
	AddPage(m_Tab, "卡密充值", m_Refill, IDD_DIALOG_PAGE_REFILL);
	AddPage(m_Tab, "设 置",m_SetingPage,IDD_DIALOG_PAGE_SETING);
	m_Tab.SetPadding(CSize(30, 10));
	m_Tab.SetMinTabWidth(50);
	m_Tab.SetCurSel(0);
	ShowPage(m_Tab);

	/*
	*
	*/
	m_MakePage.InitCtrlContext();
	m_MakePage.LoadConfig();
	m_SetingPage.LoadConfig();


	m_menu.LoadMenuA(IDR_MENU);

	//int i = mysql_query(pMySQL, "USE test01;CREATE TABLE 'cards';");

	

	InitCtrlContext();

	//启动验证服务
	//StartupServer();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartupServer, NULL, NULL, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCardsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCardsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCardsDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//int i =  m_Tab.GetCurSel();
	ShowPage(m_Tab);

}


void CCardsDlg::InitCtrlContext()
{
	// TODO: 在此处添加实现代码.
	
	//DWORD clor =  GetSysColor(COLOR_3DFACE);
	RECT rt;
	//GetWindowRect(&rt);
	//HRGN h =  CreateRoundRectRgn(5, 5, rt.right-rt.left-5,  rt.bottom-rt.top-5, 5, 5);
	//SetWindowRgn(h,FALSE);

}


BOOL CCardsDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ser.stop();
	m_MakePage.SaveConfig();
	m_SetingPage.SaveConfig();

	/*
	* 
	*/
	CardsManage* pCardsManage = CardsManage::get_instance();
	if (pCardsManage)
	{
		delete pCardsManage;
	}

	return CDialogEx::DestroyWindow();
}


void CCardsDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CCardsDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CCardsDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//::AfxTermThread();
	DestroyWindow();
	exit(0);
	CDialogEx::OnOK();
	CDialogEx::OnClose();
}

CProgressCtrl* CCardsDlg::create_progress(ULONG pos, ULONG max)
{
	CProgressCtrl* prog = new CProgressCtrl;
	RECT rt;
	this->GetClientRect(&rt);
	RECT prog_rt;
	DWORD prog_w = 120, prog_h = 30;
	prog_rt.left = (rt.right - rt.left - prog_w) / 2;
	prog_rt.right = prog_rt.left + prog_w;
	prog_rt.top = (rt.bottom - rt.top - prog_h) / 2;
	prog_rt.bottom = prog_rt.top + prog_h;
	prog->Create(WS_CHILD | PBS_SMOOTH, prog_rt, this, WM_USER + 1);

	prog->SetBkColor(RGB(00, 00, 00));
	prog->SetBarColor(RGB(0x00, 0xFF, 0x00));
	prog->SetRange32(pos, max);
	prog->SetPos(0);
	prog->SetStep(1);
	//prog->ShowWindow(SW_SHOW);
	prog->SetForegroundWindow();
	return prog;
}


void CCardsDlg::free_progress(CProgressCtrl* prog)
{
	// TODO: 在此处添加实现代码.
	if (prog)
	{
		delete prog;
	}
	return ;
}
