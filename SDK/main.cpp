
#include "CardVerify.h"
#include<openssl/md5.h>
#pragma warning(disable:4996)

#pragma comment(lib,"libcrypto.lib")
using namespace std;

string machine_summary()
{
	/* 获取 cpu id*/
	int cpuinfo[4] = { 0 };
	__cpuidex(cpuinfo, 1, 0);
	char buff[255];
	sprintf_s(buff, "%.8X%.8X", cpuinfo[3], cpuinfo[0]);
	
	/* 获取硬盘序列号*/
	HANDLE h=  CreateFileA("\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (h==INVALID_HANDLE_VALUE)
	{
		return "";
	}
	DWORD retlen;
	STORAGE_PROPERTY_QUERY query;
	query.PropertyId = StorageDeviceProperty;
	query.QueryType = PropertyStandardQuery;
	STORAGE_DEVICE_DESCRIPTOR desc;
	DeviceIoControl(h, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), &desc, sizeof(desc), &retlen, NULL);
	STORAGE_DEVICE_DESCRIPTOR* pDesc;
	
	pDesc = (STORAGE_DEVICE_DESCRIPTOR*)new char[desc.Size];
	DeviceIoControl(h, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), pDesc, desc.Size, &retlen, NULL);
	strcat_s(buff, ":");
	strcat_s(buff, (char*)pDesc + pDesc->SerialNumberOffset);
	char md5buf[255] = { 0 };
	MD5((const PBYTE)buff, strlen(buff), (PBYTE)md5buf);
	char md5str[255] = { 0 };
	for (size_t i = 0; i < 16; i++)
	{
		char tmp[20] = { 0 };
		sprintf_s(tmp, "%.2X", (BYTE)md5buf[i]);
		strcat_s(md5str, tmp);
	}
	return md5str;
}

int main()
{
	CardVerify verify;
	std::string resp;
	verify.query("01lM7iaewiBusBRxJlZuywgpn4Zc6WCl", machine_summary().c_str(), resp);
	//verify.activate("00WKxf982ALhGmx2Q0AsmgEq0cbnrFvN", machine_summary().c_str(),resp);
	cout <<  U2G(resp) << endl;
	return 0;
}