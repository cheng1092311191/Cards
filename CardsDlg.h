
// CardsDlg.h: 头文件
//

#pragma once
#include"CDlgManage.h"
#include"CDlgMake.h"
#include"CDlgSeting.h"
#include"CardsManage.h"
#include"CDlgRefill.h"
#include"CDlgOnLine.h"

// CCardsDlg 对话框
class CCardsDlg : public CDialogEx
{
// 构造
public:
	CCardsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARDS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);

public:
	CDlgOnLine m_OnLinePage;
	CDlgManage m_ManagePage;
	CDlgMake   m_MakePage;
	CDlgSeting m_SetingPage;
	CDlgRefill m_Refill;
	void InitCtrlContext();
	virtual BOOL DestroyWindow();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();

	/*
	* 创建一个进度条
	*/
	CProgressCtrl* create_progress(ULONG pos, ULONG max);
	void free_progress(CProgressCtrl* prog);
	CMenu m_menu;
};
