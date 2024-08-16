// CDlgSeting.cpp: 实现文件
//

#include "pch.h"
#include "Cards.h"
#include "CDlgSeting.h"
#include "afxdialogex.h"

#include"help.h"
#include"HttpServer.h"
// CDlgSeting 对话框

IMPLEMENT_DYNAMIC(CDlgSeting, CDialogEx)

CDlgSeting::CDlgSeting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PAGE_SETING, pParent)
	, m_Notice(_T(""))
{

}

CDlgSeting::~CDlgSeting()
{
}

void CDlgSeting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NOTICE, m_Notice);
}


BEGIN_MESSAGE_MAP(CDlgSeting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SETING, &CDlgSeting::OnBnClickedButtonApply)
END_MESSAGE_MAP()


// CDlgSeting 消息处理程序


void CDlgSeting::SaveConfig()
{
	// TODO: 在此处添加实现代码.

	
}


void CDlgSeting::LoadConfig()
{
	// TODO: 在此处添加实现代码.
	m_Notice.Preallocate(1024);

	GetPrivateProfileStringA("Seting", "Notice",NULL, m_Notice.GetBuffer(),1024, CARD_CONFIG_FILE);
	UpdateData(FALSE);
	set_notice(m_Notice.GetBuffer());
}


void CDlgSeting::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgSeting::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CDlgSeting::OnBnClickedButtonApply()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	WritePrivateProfileStringA("Seting", "Notice", m_Notice, CARD_CONFIG_FILE);
	set_notice(m_Notice.GetBuffer());
}


BOOL CDlgSeting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD exstyle =  this->GetDlgItem(IDC_EDIT_NOTICE)->GetStyle();
	//this->GetDlgItem(IDC_EDIT_NOTICE)->ModifyStyle(0,ES_MULTILINE|ES_AUTOVSCROLL);
	//SetWindowLongA(this->GetDlgItem(IDC_EDIT_NOTICE)->GetSafeHwnd(), GWL_STYLE, exstyle | ES_MULTILINE | ES_AUTOVSCROLL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
