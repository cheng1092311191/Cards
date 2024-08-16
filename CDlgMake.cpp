// CDlgMake.cpp: 实现文件
//

#include "pch.h"
#include "Cards.h"
#include "CDlgMake.h"
#include "afxdialogex.h"
#include"help.h"
#include"CardsDlg.h"
// CDlgMake 对话框

IMPLEMENT_DYNAMIC(CDlgMake, CDialogEx)

CDlgMake::CDlgMake(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PAGE_MAKE, pParent)
	, m_Number(0)
	, m_Time(0)
	, m_Type(0)
{

}

CDlgMake::~CDlgMake()
{
}

void CDlgMake::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_Number);
	DDX_CBIndex(pDX, IDC_COMBO_TIME, m_Time);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_Type);
	DDX_Control(pDX, IDC_LIST_MAKE, m_List);
}


BEGIN_MESSAGE_MAP(CDlgMake, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CDlgMake::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_MAKE, &CDlgMake::OnBnClickedButtonMake)
	ON_BN_CLICKED(IDC_BUTTON_TOSTORE, &CDlgMake::OnBnClickedButtonTostore)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgMake::OnBnClickedButtonExport)
END_MESSAGE_MAP()


// CDlgMake 消息处理程序
#include<CommCtrl.h>
/*
* 初始化控件内容
*/
void CDlgMake::InitCtrlContext()
{
	
	CComboBox* pComboxType = (CComboBox*)this->GetDlgItem(IDC_COMBO_TYPE);
	pComboxType->InsertString(-1,"会员卡");
	pComboxType->InsertString(-1, "充值卡");
	pComboxType->InsertString(-1, "测试卡");

	CComboBox* pComboxTime = (CComboBox*)this->GetDlgItem(IDC_COMBO_TIME);

	pComboxTime->InsertString(-1,"1周");
	pComboxTime->InsertString(-1,"1月");
	pComboxTime->InsertString(-1,"1季");
	pComboxTime->InsertString(-1,"1年");
	
	
	m_List.InsertColumn(0, "序号", LVCFMT_CENTER, 50);
	m_List.InsertColumn(1, "卡密", LVCFMT_CENTER, 150);
	m_List.InsertColumn(2, "卡密生成日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(3, "截止激活日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(4, "类型", LVCFMT_CENTER, 50);
	m_List.InsertColumn(5, "是否绑定", LVCFMT_CENTER, 80);
	//m_List.InsertColumn(6, "时长", LVCFMT_CENTER, 50);
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_DOUBLEBUFFER );
	//m_List.ModifyStyleEx(NULL, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
/*
* 加载配置信息
*/
void CDlgMake::LoadConfig()
{
	m_Type =  GetPrivateProfileIntA("Make", "Type", NULL, CARD_CONFIG_FILE);
	m_Time =  GetPrivateProfileIntA("Make", "Time", NULL, CARD_CONFIG_FILE);
	m_Number = GetPrivateProfileIntA("Make", "Number", NULL, CARD_CONFIG_FILE);


	UpdateData(FALSE);
}

void CDlgMake::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgMake::OnBnClickedButtonMake()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString TimeStr;
	CString ValidTimeStr;
	CString TypeStr;
	CString TimeIdStr;
	CString IsBindStr;

	CardType Type;
	/*
	* 设置卡密类型
	*/
	Type = comb_i2type(m_Type);

	ULONG32 Time;
	/*
	* 设置时长
	*/
	switch (m_Time)
	{
	case 0:
		//TimeType = CardTime::Week;
		// 1周
		Time = 3600 * 24  *7;
		
		break;
	case 1:
		//TimeType = CardTime::Month;
		// 1月
		Time = 3600 * 24 * 30;
		break;
	case 2:
		//TimeType = CardTime::Quarter;
		//1季
		Time = 3600 * 24 * 30*3;
		break;
	default:
		//TimeType = CardTime::Year;
		//1年
		Time = 3600 * 24 * 30 * 12;
	}



	MakeCards(m_MakeData, m_Number, Type, Time, "admin");


	m_List.DeleteAllItems();
	size_t n = m_MakeData.size();
	for (int i = 0; i <n; i++)
	{
		
		char NumStr[40] = { 0 };
		_itoa_s(i, NumStr, 10);
		int index = m_List.InsertItem(i, NumStr);


		//key
		m_List.SetItemText(index,  1, m_MakeData[i].key);

		Time2str(m_MakeData[i].MakeDate, TimeStr);
		m_List.SetItemText(index,  2, TimeStr);

		Time2str(m_MakeData[i].ValidDate, ValidTimeStr);
		m_List.SetItemText(index,  3, ValidTimeStr);

		//type
		TypeStr.Format("%d", m_MakeData[i].Type);
		m_List.SetItemText(index,  4, TypeStr);

	
		handle_event();
	}

}


void CDlgMake::SaveConfig()
{
	// TODO: 在此处添加实现代码.

	UpdateData(TRUE);

	char val[40] = { 0 };
	_itoa_s(m_Type, val, 10);
	WritePrivateProfileStringA("Make", "Type",val , CARD_CONFIG_FILE);
	_itoa_s(m_Time, val, 10);
	WritePrivateProfileStringA("Make", "Time", val, CARD_CONFIG_FILE);
	_itoa_s(m_Number, val, 10);
	WritePrivateProfileStringA("Make", "Number", val, CARD_CONFIG_FILE);
	
}


BOOL CDlgMake::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CDialogEx::DestroyWindow();
}

/*
* 入库按钮
*/
void CDlgMake::OnBnClickedButtonTostore()
{
	// TODO: 在此添加控件通知处理程序代码
	CCardsDlg* parent = (CCardsDlg*)::AfxGetMainWnd();
	CProgressCtrl * prog = (CProgressCtrl*)parent->create_progress(0,m_MakeData.size());
	CardsManage* pCardsManage = CardsManage::get_instance();
	prog->ShowWindow(SW_SHOW);
	for (int i = 0; i < m_MakeData.size(); i++)
	{
		
		pCardsManage->insert_card(&(m_MakeData.at(i)));
		prog->StepIt();
		handle_event();
		

	}
	parent->free_progress(prog);
}


void CDlgMake::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgMake::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CDlgMake::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog file(FALSE,"txt");
	if (file.DoModal() != IDOK)
	{
		return;
	}
	CString path = file.GetPathName();
	HANDLE h = INVALID_HANDLE_VALUE;
	if (PathFileExistsA(path))
	{
		h = CreateFileA(path, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else
	{
		h = CreateFileA(path, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	if (h==INVALID_HANDLE_VALUE)
	{
		::AfxMessageBox("创建文件失败!", MB_ICONERROR);
		return;
	}
	for (size_t i = 0; i < m_MakeData.size(); i++)
	{
		Card data = m_MakeData.at(i);
		WriteFile(h, data.key, strlen(data.key), NULL, NULL);
		WriteFile(h, "\n", 1, NULL, NULL);

	}
	CloseHandle(h);
	::AfxMessageBox("导出完成!");
	char notepad[MAX_PATH]="notepad ";
	StrCatA(notepad, path);
	WinExec(notepad,SW_SHOW);

}

