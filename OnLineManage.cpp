#include"pch.h"
#include"OnLineManage.h"


/*
* 
* 
* 管理在线列表
*/
COnLineManage g_LineManage;

COnLineManage::COnLineManage()
{
	m_MaxOnLine = 3000;
	m_OnlineList.reserve(3000);
	//Card tmp = { 1,"woshikami",0 };
	//this->OnLine(tmp);
}

COnLineManage::COnLineManage(size_t MaxOnLine)
{
	m_MaxOnLine = MaxOnLine;
	m_OnlineList.reserve(MaxOnLine);
}

COnLineManage::~COnLineManage()
{
}

BOOL COnLineManage::OnLine(Card &c)
{
	OnLine_t ol;
	ol.the = c;
	ol.OnLineTime = time(NULL);
	ol.Duration = 0;
	if (m_OnlineList.size() >= m_MaxOnLine)
	{
		// 上限了
		return FALSE;
	}
	m_OnlineList.push_back(ol);
	
	return TRUE;
}

BOOL COnLineManage::OffLine(Card& c)
{
	vector<OnLine_t>::iterator the =  this->Find(c);
	if (the != m_OnlineList.end())
	{
		m_OnlineList.erase(the);
		return TRUE;
	}
	return FALSE;
}


BOOL COnLineManage::IsOnLine(Card & c)
{
	
	return this->Find(c)!= m_OnlineList.end();
}

size_t COnLineManage::GetOnLineNumber()
{
	
	return m_OnlineList.size();
}

size_t COnLineManage::GetMaxOnLineNumber()
{
	return m_MaxOnLine;
}

OnLine_t COnLineManage::At(int i)
{
	return m_OnlineList.at(i);
}



vector<OnLine_t>::iterator COnLineManage::Find(Card& c)
{
	vector<OnLine_t>::iterator begin = m_OnlineList.begin(), end = m_OnlineList.end();
	for (; begin != end; begin++)
	{
		if (strcmp(begin->the.key, c.key) == 0)
		{
			
			break;
		}

	}

	return begin;
}
