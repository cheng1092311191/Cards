#pragma once
#include"OnLineManage.h"
#include"help.h"
enum list_online
{
	list_online_key			= 1	,
	list_online_type			,
	list_online_endtime			,
	list_online_softname		,
	list_online_device			,
	list_online_onlinetime		,
	list_online_duration		,
};
// CDlgOnLine 对话框

class CDlgOnLine : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOnLine)

public:
	CDlgOnLine(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgOnLine();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE_ONLINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void InitCtrlContext();
	CListCtrl m_List;
	afx_msg void OnLvnGetdispinfoListOnline(NMHDR* pNMHDR, LRESULT* pResult);
};
