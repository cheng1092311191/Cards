

#pragma once
#include"cpp-httplib/httplib.h"


enum card_server
{
	ok,					//����ɹ�
	missing_param = 400,	//ȱ�ٲ���
	invalid_param,			//��Ч����
	card_ban=450,		//���ܱ����
	card_expired,		//�����ѵ���
	card_activate,		//�����ѱ�����
	activate_fail=500,	//����ʧ��
	
	unknown = 800,	//δ֪����
};

using namespace httplib;
extern Server ser;
bool StartupServer();
void set_notice(std::string str);