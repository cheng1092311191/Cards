#pragma once
#include<stdio.h>
enum CardStatus
{
	nonActivated = 1,//未激活
	Activate,	//已激活
	Expired,	//已过期
};
enum CardType
{

	VPI = 1,	//会员卡
	Refill,		//充值卡
	Test,		//测试卡
};
enum CardTime
{

	Week = 1,	//周
	Month,		//月
	Quarter,	//季
	Year,		//年
};

class Card
{
public:
	int status;                    //卡密状态
	char key[255];				 //卡密
	time_t MakeDate;                //生成时间
	time_t ValidDate;                //卡密有效期限
	time_t FirstVerifyTime;        // 首次验证时间
	time_t EndTime;                 //卡密到期时间
	ULONG32	Time;					//卡密时长   秒
	char Generator[255];             //生成者
	char SoftName[255];             //软件名
	int Type;                    //卡密类型
	char Device[255];			//设备
	bool ban;				//封禁

public:
	const char* status_str();

	const char* type_str();

};
