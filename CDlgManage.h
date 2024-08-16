#pragma once
#include"CardsManage.h"

// CDlgManage 对话框

class CDlgManage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgManage)

public:
	CDlgManage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE_MANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	CString m_key;
	void InitCtrlContext();
	afx_msg void OnBnClickedButtonStorage();
	afx_msg void OnBnClickedButtonLookup();

	int insert_card( Card &data);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	CComboBox m_comb_status;
	CComboBox m_comb_type;
	afx_msg void OnRclickListManage(NMHDR* pNMHDR, LRESULT* pResult);

public:
	afx_msg void OnCheckAll();
	afx_msg void OnCheckCancel();
	afx_msg void OnCopy();
	afx_msg void OnExport();
	afx_msg void OnRefill();
	afx_msg void OnBan();
	afx_msg void OnUnban();
private:
	int list_check_count(std::vector<int>* checks =nullptr);
public:
//	afx_msg void OnRdblclkListManage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListManage(NMHDR* pNMHDR, LRESULT* pResult);
};
