// CDlgRefill.cpp: 实现文件
//

#include "pch.h"
#include "Cards.h"
#include "CDlgRefill.h"
#include "afxdialogex.h"
#include"CardsDlg.h"

// CDlgRefill 对话框

IMPLEMENT_DYNAMIC(CDlgRefill, CDialogEx)

CDlgRefill::CDlgRefill(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PAGE_REFILL, pParent)
{

}

CDlgRefill::~CDlgRefill()
{
}

void CDlgRefill::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REFILL, m_List);
}


BEGIN_MESSAGE_MAP(CDlgRefill, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_TOLIST, &CDlgRefill::OnBnClickedButtonTolist)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_REFILL, &CDlgRefill::OnRclickListRefill)
	ON_COMMAND(ID_REMOVE, &CDlgRefill::OnRemove)
END_MESSAGE_MAP()


// CDlgRefill 消息处理程序


void CDlgRefill::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgRefill::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CDlgRefill::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnCancel();
	CDialogEx::OnClose();
}


void CDlgRefill::OnBnClickedButtonTolist()
{
	// TODO: 在此添加控件通知处理程序代码
	CString key;
	CString strindex;
	int i;
	GetDlgItemTextA(IDC_EDIT_REFILLKEY, key);
	i = m_List.GetItemCount();
	strindex.Format("%d",i);
	m_List.InsertItem(i, strindex);
	m_List.SetItemText(i, 1, key);


	SetDlgItemTextA(IDC_EDIT_REFILLKEY, "");
}


BOOL CDlgRefill::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_List.InsertColumn(0, "索引",0,50);
	m_List.InsertColumn(1, "卡密",0,200);
	m_List.InsertColumn(2, "状态",0,80);
	m_List.InsertColumn(3, "到期时间",0,200);
	m_List.InsertColumn(4, "结果",0,80);
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER );

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgRefill::OnRclickListRefill(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMItemActivate->iItem==-1)
	{
		return;
	}
	POINT pt;
	GetCursorPos(&pt);

	CCardsDlg* parent =(CCardsDlg*)AfxGetMainWnd();
	CMenu*  sub = parent->m_menu.GetSubMenu(1);
	sub->TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_VERPOSANIMATION | TPM_LEFTBUTTON, pt.x, pt.y, this);

	
}


/*
* 菜单处理
*/

void CDlgRefill::OnRemove()
{
	// TODO: 在此添加命令处理程序代码
	m_List.DeleteItem(m_List.GetSelectionMark());
}
