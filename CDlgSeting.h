#pragma once


// CDlgSeting 对话框

class CDlgSeting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSeting)

public:
	CDlgSeting(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSeting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE_SETING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SaveConfig();
	void LoadConfig();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonApply();
	virtual BOOL OnInitDialog();
	CString m_Notice;
};
