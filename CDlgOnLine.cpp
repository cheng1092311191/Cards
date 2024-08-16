// CDlgOnLine.cpp: 实现文件
//

#include "pch.h"
#include "Cards.h"
#include "CDlgOnLine.h"
#include "afxdialogex.h"


// CDlgOnLine 对话框

IMPLEMENT_DYNAMIC(CDlgOnLine, CDialogEx)

CDlgOnLine::CDlgOnLine(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PAGE_ONLINE, pParent)
{

}

CDlgOnLine::~CDlgOnLine()
{
}

void CDlgOnLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOnLine, CDialogEx)
END_MESSAGE_MAP()


// CDlgOnLine 消息处理程序
