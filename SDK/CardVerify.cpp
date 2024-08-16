#include"CardVerify.h"

using namespace std;


std::string U2G(const std::string& utf8)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//¼Ó1ÓÃÓÚ½Ø¶Ï×Ö·û´® 
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

// GBK×Ö·û´®×ª³ÉjsonÊ¶±ğµÄUTF8×Ö·û´®
std::string G2U(const std::string& gbk)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//¼Ó1ÓÃÓÚ½Ø¶Ï×Ö·û´® 
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







CardVerify::CardVerify()
{
	m_pCli = new Client("192.168.3.3", 5050);
	
	assert(m_pCli->is_valid());

}

CardVerify::~CardVerify()
{
	if (m_pCli)
	{
		delete m_pCli;
	}
}

bool CardVerify::query(const char* key, const char* device,std::string& response_content)
{

	std::string url("/Query");
	url.append("?Key=");
	url.append(key);
	url.append("&Device=");
	url.append(device);
	Result rel =  m_pCli->Get(url);
	Response res =  rel.value();
	response_content = res.body;
	
	return res.status == OK_200;
}

bool CardVerify::activate(const char* key, const char* device, std::string& response_content)
{
	std::string url("/Activate");
	std::string param;
	param.append("Key=");
	param.append(key);
	param.append("&Device=");
	param.append(device);
	url += "?" + param;

	Result rel = m_pCli->Get(url);
	Response res = rel.value();
	response_content = res.body;

	return res.status == OK_200;
}
