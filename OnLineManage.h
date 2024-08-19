#pragma once

#include<vector>
#include"CardStruct.h"
using namespace std;


struct OnLine_t
{
	Card the;
	//����ʱ��
	time_t OnLineTime;
	//����ʱ�� �뵥λ
	time_t Duration;
	CString Duration_str()
	{

		//��С��λ ��  ���λ �� 

		time_t time = Duration;
		int day=0, hour=0, min=0, sec = 0;
		int sunMin, sunHour;
		CString Buf;
		


		sec = time % 60;
		//�����ٷ���
		sunMin =time / 60 ;
		//������Сʱ
		sunHour = sunMin / 60;

		day = sunHour / 24;
		min = sunMin % 60;
		hour = sunHour % 24;

		//����
		if (day)
		{
			Buf.AppendFormat("%d��", day);
		}

		//Сʱ
		if (hour)
		{
			Buf.AppendFormat("%dСʱ", hour);
		}

		//����
		if (min&&  day==0)
		{
			Buf.AppendFormat("%d����", min);
		}

		//��
		if (min&& day==0&& hour==0 )
		{
			Buf.AppendFormat("%d��", sec);
		}

		
		return Buf;
	}
};


/*
* ���߹�������
*/
class COnLineManage
{
public:
	COnLineManage();
	COnLineManage(size_t MaxOnLine);

	~COnLineManage();
	/* ���� */
	BOOL OnLine(Card& c);
	/* ���� */
	BOOL OffLine(Card& c);
	/* �Ƿ����� */
	BOOL IsOnLine(Card& c);
	/* ��ȡ��ǰ������ */
	size_t GetOnLineNumber();
	/* ��ȡ������������� */
	size_t GetMaxOnLineNumber();
	OnLine_t At(int i);
private:
	/* ����ָ������ */
	vector<OnLine_t>::iterator Find(Card& c);
private:
	vector<OnLine_t> m_OnlineList;
	size_t m_MaxOnLine;
};

extern COnLineManage g_LineManage;