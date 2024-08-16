#pragma once


// CDlgMySQLConnect 对话框

class CDlgMySQLConnect : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMySQLConnect)

public:
	CDlgMySQLConnect(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgMySQLConnect();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MYSQL_CONNECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	CString m_Host;
	CString m_Port;
	CString m_User;
	CString m_Pass;
	void SaveConfig();
	void LoadConfig();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
};
