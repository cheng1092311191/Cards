#include"pch.h"
#include"help.h"
#include<iostream>
std::string U2G(const std::string& utf8)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//加1用于截断字符串 
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

// GBK字符串转成json识别的UTF8字符串
std::string G2U(const std::string& gbk)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//加1用于截断字符串 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), gbk.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}



char StrTab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
/*
* 生成32位随机字母
*/
int MakeKey32(char* Buff)
{

	int i = 0;
	for (; i < 32; i++)
	{
		int n = rand() % (sizeof(StrTab)-1);
		Buff[i] = StrTab[n];
	}
	return i;
}


std::vector<CDialogEx*> TabPages;


int AddPage(CTabCtrl& Tab, const char* text, CDialogEx& Page,UINT nID ,int nImage)
{
	int i = Tab.InsertItem(Tab.GetItemCount(), text, nImage);
	if (i != -1)
	{
		Page.Create(nID, &Tab);
		CRect rt;
		Tab.GetClientRect(&rt);
		DWORD w = rt.right - rt.left;
		DWORD h = rt.bottom - rt.top;
		DWORD child_h = h - 40;
		DWORD child_w = w - 10;
		CSize size;
		
		Page.MoveWindow(4,38, child_w, child_h);

		TabPages.push_back(&Page);
	}
	return i;
}

bool ShowPage(CTabCtrl& Tab)
{
	int sel = Tab.GetCurSel();
	if (sel == -1)
	{
		return false;
	}

	for (int j = 0; j < TabPages.size(); j++)
	{
		CDialogEx* pPage = TabPages.at(j);
		if (sel == j)
		{

			pPage->ShowWindow(SW_SHOW);
		}
		else {
			pPage->ShowWindow(SW_HIDE);
		}
	}
	return true;
}
/*
* time 时间转换 字符串格式
*/
void Time2str(time_t time, CString &Buf)
{
	tm t;
	Buf = "";
	if (time==NULL)
	{
		return;
	}
	localtime_s(&t, &time);
	Buf.Format( "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", t.tm_year + 1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}

/*
* 生产卡密
*/
int MakeCards(std::vector<Card> & arr,int Num,CardType Type,ULONG32 Time,const char* Generator)
{
	arr.clear();
	int i = 0;
	for (; i < Num; i++)
	{
		Card crd = { 0 };
		crd.Type = Type;
		crd.Time = Time;
		crd.MakeDate = time(NULL);
		crd.ValidDate = time(NULL)+ 31536000;//1年
		crd.status = nonActivated;
		memcpy(crd.Generator, Generator, MAX_PATH);
	

		MakeKey32(crd.key);
		arr.push_back(crd);
	}
	return i;
}

void handle_event()
{
	/*
* 处理事件
*/
	MSG msg;
	BOOL ok = 0;
	while ( PeekMessageA(&msg, 0, 0, 0, 0))
	{
		if (GetMessageA(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

	}
}

CardStatus comb_i2status(int i)
{
	switch (i)
	{
	case 0:
		return CardStatus::nonActivated;
	case 1:
		return CardStatus::Activate;
	case 2:
		return CardStatus::Expired;
		
	}
	return CardStatus(NULL);
}

CardType comb_i2type(int i)
{
	switch (i)
	{
	case 0:
		return CardType::VPI;
	case 1:
		return CardType::Refill;
	case 2:
		return CardType::Test;
	}
	return CardType(NULL);
}
