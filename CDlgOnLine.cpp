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
	DDX_Control(pDX, IDC_LIST_ONLINE, m_List);
}


BEGIN_MESSAGE_MAP(CDlgOnLine, CDialogEx)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_ONLINE, &CDlgOnLine::OnLvnGetdispinfoListOnline)
END_MESSAGE_MAP()


// CDlgOnLine 消息处理程序


BOOL CDlgOnLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCtrlContext();





	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgOnLine::InitCtrlContext()
{
	CRect rect;
	m_List.GetWindowRect( &rect);
	DWORD exStyle = m_List.GetExStyle();
	DWORD Style = m_List.GetStyle();
	m_List.DestroyWindow();

	/* 创建虚表 */
	BOOL ok = m_List.CreateEx(exStyle ,
		Style  |LVS_OWNERDATA , CRect(5,5,rect.Width()+5,rect.Height()+5), this, IDC_LIST_ONLINE);
	m_List.ShowWindow(SW_SHOW);
	m_List.InsertColumn(0, "序号", LVCFMT_CENTER, 50);
	m_List.InsertColumn(list_online_key, "卡密", LVCFMT_CENTER, 150);
	m_List.InsertColumn(list_online_type, "类型", LVCFMT_CENTER, 50);
	//m_List.InsertColumn(list_online_firstverifytime, "首次验证日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(list_online_endtime, "卡密到期日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(list_online_softname, "软件名称", LVCFMT_CENTER,80);
	m_List.InsertColumn(list_online_device, "设备", LVCFMT_CENTER, 120);

	//list_online_onlinetime
	m_List.InsertColumn(list_online_onlinetime, "上线时间", LVCFMT_CENTER, 120);
	//list_online_duration
	m_List.InsertColumn(list_online_duration, "在线时长", LVCFMT_CENTER, 80);
	//m_List.ModifyStyle(0, LVS_OWNERDATA);
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_List.SetItemCountEx(100);

}


void CDlgOnLine::OnLvnGetdispinfoListOnline(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pDispInfo->item.iItem>= g_LineManage.GetOnLineNumber())
	{
		*pResult = 0;
		return;
	}
	OnLine_t ol =  g_LineManage.At(pDispInfo->item.iItem);
	
	if (pDispInfo->item.mask& LVIF_TEXT )
	{
		CString str;
		switch (pDispInfo->item.iSubItem)
		{
		case 0:
			str.Format("%d", pDispInfo->item.iItem);
			break;
		case list_online_key:
			str= ol.the.key;
			break;
		case list_online_type:
			str =  ol.the.type_str();
			break;
		case list_online_endtime:
			Time2str(ol.the.EndTime, str);
			break;
		case list_online_softname:
			str = ol.the.SoftName;
			break;
		case list_online_device:
			str = ol.the.Device;
			break;
		case list_online_onlinetime:
			Time2str(ol.OnLineTime, str);
			break;
		case list_online_duration:
			str =  ol.Duration_str();
			break;
		default:
			break;
		}
		strcpy_s(pDispInfo->item.pszText, pDispInfo->item.cchTextMax, str.GetBuffer());
	}

	*pResult = 0;
}
