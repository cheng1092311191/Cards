#pragma once


// CDlgRefill 对话框

class CDlgRefill : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRefill)

public:
	CDlgRefill(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgRefill();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE_REFILL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonTolist();
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnRclickListRefill(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemove();
};
