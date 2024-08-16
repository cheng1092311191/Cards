#pragma once
#include"CardsManage.h"
#include<vector>
// CDlgMake 对话框

class CDlgMake : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMake)

public:
	CDlgMake(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgMake();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE_MAKE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	void InitCtrlContext();
	void LoadConfig();
	int m_Number;
	int m_Time;
	int m_Type;
	CListCtrl m_List;
	std::vector<Card> m_MakeData;

	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedButtonMake();
	void SaveConfig();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonTostore();

private:
	
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonExport();
};
