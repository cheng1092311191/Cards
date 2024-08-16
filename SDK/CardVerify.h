#pragma once
#include"../cpp-httplib/httplib.h"
#include"../CardStruct.h"
#include"../json/include/nlohmann/json.hpp"

#include<Windows.h>
using namespace httplib;

class CardVerify
{
public:
	CardVerify();
	~CardVerify();


	bool query(const char* key, const char* device,std::string & response_content);
	bool activate(const char* key,const char* device,std::string & response_content);
private:

	Client* m_pCli;
};

// GBK字符串转成json识别的UTF8字符串
std::string G2U(const std::string& gbk);
std::string U2G(const std::string& utf8);
