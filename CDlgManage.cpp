// CDlgManage.cpp: 实现文件
//

#include "pch.h"
#include "Cards.h"
#include "CDlgManage.h"
#include "afxdialogex.h"
#include"CardsManage.h"
#include"CardsDlg.h"
#include"help.h"



#define		LIST_MANAGE_KEY			1
#define		LIST_MANAGE_MAKEDATE	2
#define		LIST_MANAGE_VALIDDATE	3
#define		LIST_MANAGE_STATUS		4
#define		LIST_MANAGE_TYPE		5
#define		LIST_MANAGE_FIRSTVERIFYTIME	6
#define		LIST_MANAGE_ENDTIME		7
#define		LIST_MANAGE_SOFTNAME	8
#define		LIST_MANAGE_DEVICE		9
#define		LIST_MANAGE_ISBIND		10



// CDlgManage 对话框

IMPLEMENT_DYNAMIC(CDlgManage, CDialogEx)

CDlgManage::CDlgManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PAGE_MANAGE, pParent)
	, m_key(_T(""))
{

}

CDlgManage::~CDlgManage()
{
}

void CDlgManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	DDX_Control(pDX, IDC_COMBO_WHERE, m_comb_status);
	DDX_Control(pDX, IDC_COMBO_CARD_TYPE, m_comb_type);
}


BEGIN_MESSAGE_MAP(CDlgManage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_STORAGE, &CDlgManage::OnBnClickedButtonStorage)
	ON_BN_CLICKED(IDC_BUTTON_LOOKUP, &CDlgManage::OnBnClickedButtonLookup)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MANAGE, &CDlgManage::OnRclickListManage)
	ON_COMMAND(ID_CHECK_ALL, &CDlgManage::OnCheckAll)
	ON_COMMAND(ID_CHECK_CANCEL, &CDlgManage::OnCheckCancel)
	ON_COMMAND(ID_COPY, &CDlgManage::OnCopy)
	ON_COMMAND(ID_EXPORT, &CDlgManage::OnExport)
	ON_COMMAND(ID_REFILL, &CDlgManage::OnRefill)
	ON_COMMAND(ID_BAN, &CDlgManage::OnBan)
	ON_COMMAND(ID_UNBAN, &CDlgManage::OnUnban)
//	ON_NOTIFY(NM_RDBLCLK, IDC_LIST_MANAGE, &CDlgManage::OnRdblclkListManage)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_MANAGE, &CDlgManage::OnDblclkListManage)
END_MESSAGE_MAP()


// CDlgManage 消息处理程序


BOOL CDlgManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化



	this->InitCtrlContext();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgManage::InitCtrlContext()
{
	// TODO: 在此处添加实现代码.
	m_List.InsertColumn(0, "序号", LVCFMT_CENTER, 50);
	m_List.InsertColumn(LIST_MANAGE_KEY, "卡密", LVCFMT_CENTER, 200);
	m_List.InsertColumn(LIST_MANAGE_MAKEDATE, "卡密生成日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(LIST_MANAGE_VALIDDATE, "截止激活日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(LIST_MANAGE_STATUS, "状态", LVCFMT_CENTER, 60);
	m_List.InsertColumn(LIST_MANAGE_TYPE, "类型", LVCFMT_CENTER, 50);
	m_List.InsertColumn(LIST_MANAGE_FIRSTVERIFYTIME, "首次验证日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(LIST_MANAGE_ENDTIME, "卡密到期日期", LVCFMT_CENTER, 120);
	m_List.InsertColumn(LIST_MANAGE_SOFTNAME, "软件名称", LVCFMT_CENTER, 80);
	m_List.InsertColumn(LIST_MANAGE_DEVICE, "设备", LVCFMT_CENTER, 200);
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER| LVS_EX_CHECKBOXES);

	//::SetWindowTheme(m_List.GetSafeHwnd(), L"Explorer", NULL);

	m_comb_status.InsertString(-1, "全部");
	m_comb_status.InsertString(-1, "未激活");
	m_comb_status.InsertString(-1, "已使用");
	m_comb_status.InsertString(-1, "已到期");
	m_comb_status.SetCurSel(0);

	m_comb_type.InsertString(-1, "全部");
	m_comb_type.InsertString(-1, "会员卡");
	m_comb_type.InsertString(-1, "充值卡");
	m_comb_type.InsertString(-1, "测试卡");
	m_comb_type.SetCurSel(0);



	//DWORD val = TRUE;
	////设置开启菜单幻灯片动画
	//BOOL ok = SystemParametersInfoA(SPI_SETMENUFADE, NULL, &val, NULL);

	////开启动画
	//val = TRUE;
	//ok = SystemParametersInfoA(SPI_SETMENUANIMATION, NULL, &val, NULL);

}


/*
* 查询库存按钮
*/
void CDlgManage::OnBnClickedButtonStorage()
{
	// TODO: 在此添加控件通知处理程序代码
	// 禁止查找按钮
	GetDlgItem(IDC_BUTTON_LOOKUP)->EnableWindow(FALSE);
	std::vector<Card> arr;

	CCardsDlg* parent = (CCardsDlg*)::AfxGetMainWnd();
	CProgressCtrl* prog = ((CCardsDlg*)::AfxGetMainWnd())->create_progress(0, 100);


	CardsManage* pCardsManage = CardsManage::get_instance();
	/*
	* 条件
	*/
	char where_buf[255] = { 0 };


	int	 type =  m_comb_type.GetCurSel();
	int  status = m_comb_status.GetCurSel();
	if (type==NULL && status==NULL)goto _query;

	/*
	* 卡密状态,类型的条件
	*/

	if (type && status)
	{
		sprintf_s(where_buf, "card_type=%d and card_status=%d", type,status);
	}
	else if (type && status==NULL)
	{
		sprintf_s(where_buf, "card_type=%d ", type);
	}
	else if (type == NULL && status)
	{
		sprintf_s(where_buf, "card_status=%d ", status);
	}

	
_query:
	size_t num =  pCardsManage->query_where(arr, where_buf);
	if (num==0)
	{
		::AfxMessageBox("无记录!");
		goto _ret;
	}
	prog->SetRange32(0, num);
	m_List.DeleteAllItems();
	prog->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_LOOKUP)->EnableWindow(FALSE);
	//锁住绘图
	m_List.LockWindowUpdate();
	for (size_t i = 0; i < arr.size(); i++)
	{

		insert_card(arr[i]);
		prog->StepIt();
		
	}
	//解锁绘图
	m_List.UnlockWindowUpdate();
_ret:
	parent->free_progress(prog);
	//恢复查找按钮
	GetDlgItem(IDC_BUTTON_LOOKUP)->EnableWindow(TRUE);
}


void CDlgManage::OnBnClickedButtonLookup()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CardsManage* pCardsManage = CardsManage::get_instance();
	Card data = { 0 };
	size_t num = pCardsManage->query_key(m_key, data);
	if (num)
	{
		m_List.DeleteAllItems();
		insert_card(data);
		//CardsManage* pCardsManage = CardsManage::get_instance();
		//pCardsManage->change_status(data.key,CardStatus::Expired);
	}
	else
	{
		AfxMessageBox("无记录!");
	}


}

/*
* 插入一条数据到列表框
*/
int CDlgManage::insert_card( Card &data)
{
	// TODO: 在此处添加实现代码.
	CStringA Numstr;
	int i = m_List.GetItemCount();
	Numstr.Format("%d", i);
	int index = m_List.InsertItem(i, Numstr);


	//key
	m_List.SetItemText(index, LIST_MANAGE_KEY, data.key);
	//Makedate
	Time2str(data.MakeDate, Numstr);
	m_List.SetItemText(index, LIST_MANAGE_MAKEDATE, Numstr);
	//validDate
	Time2str(data.ValidDate, Numstr);
	m_List.SetItemText(index, LIST_MANAGE_VALIDDATE, Numstr);
	//status

	m_List.SetItemText(index, LIST_MANAGE_STATUS, data.status_str());
	//type

	m_List.SetItemText(index, LIST_MANAGE_TYPE, data.type_str());


	//软件名称
	m_List.SetItemText(index, LIST_MANAGE_SOFTNAME, data.SoftName);
	//FirstVerifyTime
	Time2str(data.FirstVerifyTime, Numstr);
	m_List.SetItemText(index, LIST_MANAGE_FIRSTVERIFYTIME , Numstr);
	//EndTime
	Time2str(data.EndTime, Numstr);
	m_List.SetItemText(index, LIST_MANAGE_ENDTIME, Numstr);

	//Generator
	//m_List.SetItemText(index, LIST_MANAGE_GENERATOR, data.Generator);


	//Device
	m_List.SetItemText(index, LIST_MANAGE_DEVICE, data.Device);


	//处理事件
	handle_event();
	return index;
}


void CDlgManage::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CDlgManage::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CDlgManage::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnOK();
	CDialogEx::OnClose();
}


void CDlgManage::OnRclickListManage(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	std::vector<int> checks;
	for (size_t i = 0; i < m_List.GetItemCount(); i++)
	{
		if (m_List.GetCheck(i))
			checks.push_back(i);
	}
	if (pNMItemActivate->iItem == -1 && checks.size()==0)
	{
		return;
	}

	POINT pt;
	GetCursorPos(&pt);
	CCardsDlg* parent = (CCardsDlg*)AfxGetMainWnd();

	
	CMenu* submenu = parent->m_menu.GetSubMenu(0);

	if (checks.size() == 0)
	{
		submenu->EnableMenuItem(ID_EXPORT, MF_DISABLED | MF_GRAYED);
		
	}
	else
	{
		submenu->EnableMenuItem(ID_EXPORT, MF_ENABLED);
	}



	submenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_VERPOSANIMATION| TPM_LEFTBUTTON, pt.x, pt.y, this);



	*pResult = 0;
}


/******************************************管理对话框的 菜单处理*************************************/
/*
* 勾选全部
*/
void CDlgManage::OnCheckAll()
{
	// TODO: 在此添加命令处理程序代码
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		m_List.SetCheck(i);
	}
}
/*
* 取消勾选
*/
void CDlgManage::OnCheckCancel()
{
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		m_List.SetCheck(i,FALSE);
	}
}

/*
* 复制
*/
void CDlgManage::OnCopy()
{
	// TODO: 在此添加命令处理程序代码

	/*
	* 如果没有勾选项,就只用单选中项
	*/
	std::vector<int>checks;
	int check_count = this->list_check_count(&checks);
	if (check_count==0 && m_List.GetSelectionMark()!=-1 )
	{
		checks.push_back(m_List.GetSelectionMark());
	}

	CString str;
	for (int i = 0; i < checks.size(); i++)
	{

		str += m_List.GetItemText(checks[i], LIST_MANAGE_KEY);
		if (i!=(checks.size()-1))
		{
			str.AppendChar('\n');
		}
		
		
	}


	if (OpenClipboard())
	{
		EmptyClipboard();
		// 分配内存并清零
		size_t size = static_cast<size_t>(str.GetLength()) + 1;
		HANDLE hmem =  GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
		PVOID p =  GlobalLock(hmem);
		memcpy(p, str.GetBuffer(), size);
	
		HANDLE res = SetClipboardData(CF_TEXT, hmem);
		GlobalUnlock(hmem);
		//释放
		CloseClipboard();

	} 
	
}
/*
* 导出
*/
void CDlgManage::OnExport()
{

	std::vector<int> checks;
	/*
	* 获得所有勾选项
	*/
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		if (m_List.GetCheck(i))
		{
			checks.push_back(i);
		}
	}
	if (checks.empty())
	{
		return;
	}
	CFileDialog fdlg(FALSE, "txt");

	if (fdlg.DoModal() != IDOK)
	{
		return;
	}
	CString path = fdlg.GetPathName();
	HANDLE hfile;
	if (PathFileExistsA(path))
	{
		hfile = CreateFile(path, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS,NULL, NULL);
	}
	else
	{
		hfile = CreateFile(path, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	}
	for (int i = 0; i < checks.size(); i++)
	{
		CString str = m_List.GetItemText(i, LIST_MANAGE_KEY);
		WriteFile(hfile, str.GetBuffer(), str.GetLength(),NULL,NULL);
		WriteFile(hfile, "\n", 1, NULL, NULL);
	}
	FlushFileBuffers(hfile);
	CloseHandle(hfile);
	CloseHandle(hfile);
	AfxMessageBox("导出完成");
}

/*
* 充值
*/
void CDlgManage::OnRefill()
{

}

/*
* 封禁
*/
void CDlgManage::OnBan()
{
	CardsManage* pManage =  CardsManage::get_instance();

	std::vector<int>checks;
	int check_count = this->list_check_count(&checks);
	if (check_count == 0 && m_List.GetSelectionMark() != -1)
	{
		checks.push_back(m_List.GetSelectionMark());
	}

	for (int i = 0; i < check_count; i++)
	{
		CString key = m_List.GetItemText(checks[i], LIST_MANAGE_KEY);
		pManage->change_ban(key, true);
		Card data;
		pManage->query_key(key, data);
		m_List.SetItemText(checks[i], LIST_MANAGE_STATUS, data.status_str());
	}
}
/*
* 解封
*/
void CDlgManage::OnUnban()
{
	CardsManage* pManage = CardsManage::get_instance();
	std::vector<int>checks;
	int check_count = this->list_check_count(&checks);
	if (check_count == 0 && m_List.GetSelectionMark() != -1)
	{
		checks.push_back(m_List.GetSelectionMark());
	}
	for (int i = 0; i < check_count; i++)
	{
		int sel = checks[i];
		CString key = m_List.GetItemText(sel, LIST_MANAGE_KEY);
		pManage->change_ban(key, false);
		Card data;
		pManage->query_key(key, data);
		m_List.SetItemText(sel, LIST_MANAGE_STATUS, data.status_str());
	}

}


int CDlgManage::list_check_count(std::vector<int>* checks)
{
	// TODO: 在此处添加实现代码.
	if (checks)
	{
		checks->clear();
	}
	int count = 0;
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		if (m_List.GetCheck(i))
		{
			count++;
			if (checks)
			{
				checks->push_back(i);
			}
		}
	}
	return count;
}


//void CDlgManage::OnRdblclkListManage(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//
//	*pResult = 0;
//}


void CDlgManage::OnDblclkListManage(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_List.SetCheck(pNMItemActivate->iItem, !m_List.GetCheck(pNMItemActivate->iItem));
	*pResult = 0;
}
