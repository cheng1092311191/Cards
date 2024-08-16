// CDlgMySQLConnect.cpp: 实现文件
//

#include "pch.h"
#include "Cards.h"
#include "CDlgMySQLConnect.h"
#include "afxdialogex.h"
#include"help.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
CardsManage* pCardsManage = new CardsManage;
// CDlgMySQLConnect 对话框

IMPLEMENT_DYNAMIC(CDlgMySQLConnect, CDialogEx)

CDlgMySQLConnect::CDlgMySQLConnect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MYSQL_CONNECTION, pParent)
	, m_Host(_T(""))
	, m_Port(_T(""))
	, m_User(_T(""))
	, m_Pass(_T(""))
{

}

CDlgMySQLConnect::~CDlgMySQLConnect()
{
}

void CDlgMySQLConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HOST, m_Host);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_USER, m_User);
	DDX_Text(pDX, IDC_EDIT_PASS, m_Pass);
}


BEGIN_MESSAGE_MAP(CDlgMySQLConnect, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CDlgMySQLConnect::OnBnClickedButtonConnect)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgMySQLConnect 消息处理程序


void CDlgMySQLConnect::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	this->SetDlgItemTextA(IDC_BUTTON_CONNECT, "连接中…");
	this->GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	if (pCardsManage->connect(m_Host, atoi(m_Port.GetBuffer()), m_User, m_Pass))
	{
		SaveConfig();
		this->EndDialog(IDOK);
		return;
	}
	AfxMessageBox("MySQL Connect fail!", MB_ICONERROR | MB_OK);
	this->GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	this->SetDlgItemTextA(IDC_BUTTON_CONNECT, "连接");
	return;
}


void CDlgMySQLConnect::SaveConfig()
{
	// TODO: 在此处添加实现代码.
	UpdateData(TRUE);
	WritePrivateProfileStringA("MySQL", "Host", m_Host, CARD_CONFIG_FILE);
	WritePrivateProfileStringA("MySQL", "Port", m_Port, CARD_CONFIG_FILE);
	WritePrivateProfileStringA("MySQL", "User", m_User, CARD_CONFIG_FILE);
	WritePrivateProfileStringA("MySQL", "Pass", m_Pass, CARD_CONFIG_FILE);
}


void CDlgMySQLConnect::LoadConfig()
{
	// TODO: 在此处添加实现代码.
	char val[MAX_PATH] = { 0 };
	GetPrivateProfileStringA("MySQL", "Host", NULL, val, MAX_PATH, CARD_CONFIG_FILE);
	m_Host = val;
	GetPrivateProfileStringA("MySQL", "Port", NULL, val, MAX_PATH, CARD_CONFIG_FILE);
	m_Port = val;
	GetPrivateProfileStringA("MySQL", "User", NULL, val, MAX_PATH, CARD_CONFIG_FILE);
	m_User = val;
	GetPrivateProfileStringA("MySQL", "Pass", NULL, val, MAX_PATH, CARD_CONFIG_FILE);
	m_Pass = val;

	UpdateData(FALSE);
}


void CDlgMySQLConnect::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgMySQLConnect::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CDlgMySQLConnect::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
	CDialogEx::OnCancel();
}


BOOL CDlgMySQLConnect::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	HRESULT h;
	//HTHEME hTheme = OpenThemeData(this->GetDlgItem(IDC_BUTTON_CONNECT)->GetSafeHwnd(),WC_BUTTONW);
	//RECT rt;
	//this->GetDlgItem(IDC_BUTTON_CONNECT)->GetClientRect(&rt);
	//HRESULT h = DrawThemeBackground(hTheme, this->GetDC()->m_hDC, BP_RADIOBUTTON, RBS_CHECKEDHOT, &rt, NULL);
	//CloseThemeData(hTheme);
	//h =  SetWindowTheme(this->GetSafeHwnd(),L"", L"");
	//h =  SetWindowTheme(this->GetDlgItem(IDC_BUTTON_CONNECT)->GetSafeHwnd(),L"Button", NULL);
	//h =  SetWindowTheme(this->GetSafeHwnd(),L"Edit", NULL);
	LoadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
