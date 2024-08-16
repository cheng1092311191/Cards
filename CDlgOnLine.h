#pragma once


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
};
