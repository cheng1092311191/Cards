#pragma once

#include<vector>
#include"CardStruct.h"
using namespace std;


struct OnLine_t
{
	Card the;
	//上线时间
	time_t OnLineTime;
	//在线时长 秒单位
	time_t Duration;
	CString Duration_str()
	{

		//最小单位 秒  最大单位 天 

		time_t time = Duration;
		int day=0, hour=0, min=0, sec = 0;
		int sunMin, sunHour;
		CString Buf;
		


		sec = time % 60;
		//共多少分钟
		sunMin =time / 60 ;
		//共多少小时
		sunHour = sunMin / 60;

		day = sunHour / 24;
		min = sunMin % 60;
		hour = sunHour % 24;

		//天数
		if (day)
		{
			Buf.AppendFormat("%d天", day);
		}

		//小时
		if (hour)
		{
			Buf.AppendFormat("%d小时", hour);
		}

		//分钟
		if (min&&  day==0)
		{
			Buf.AppendFormat("%d分钟", min);
		}

		//秒
		if (min&& day==0&& hour==0 )
		{
			Buf.AppendFormat("%d秒", sec);
		}

		
		return Buf;
	}
};


/*
* 在线管理数据
*/
class COnLineManage
{
public:
	COnLineManage();
	COnLineManage(size_t MaxOnLine);

	~COnLineManage();
	/* 上线 */
	BOOL OnLine(Card& c);
	/* 离线 */
	BOOL OffLine(Card& c);
	/* 是否在线 */
	BOOL IsOnLine(Card& c);
	/* 获取当前在线数 */
	size_t GetOnLineNumber();
	/* 获取最大在线数上限 */
	size_t GetMaxOnLineNumber();
	OnLine_t At(int i);
private:
	/* 查找指定卡密 */
	vector<OnLine_t>::iterator Find(Card& c);
private:
	vector<OnLine_t> m_OnlineList;
	size_t m_MaxOnLine;
};

extern COnLineManage g_LineManage;