

#pragma once
#include"cpp-httplib/httplib.h"


enum card_server
{
	ok,					//请求成功
	missing_param = 400,	//缺少参数
	invalid_param,			//无效参数
	card_ban=450,		//卡密被封禁
	card_expired,		//卡密已到期
	card_activate,		//卡密已被激活
	activate_fail=500,	//激活失败
	
	unknown = 800,	//未知错误
};

using namespace httplib;
extern Server ser;
bool StartupServer();
void set_notice(std::string str);