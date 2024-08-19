#pragma once
#include<stdio.h>
enum CardStatus
{
	nonActivated = 1,//δ����
	Activate,	//�Ѽ���
	Expired,	//�ѹ���
};
enum CardType
{

	VPI = 1,	//��Ա��
	Refill,		//��ֵ��
	Test,		//���Կ�
};
enum CardTime
{

	Week = 1,	//��
	Month,		//��
	Quarter,	//��
	Year,		//��
};

class Card
{
public:
	int status;                    //����״̬
	char key[255];				 //����
	time_t MakeDate;                //����ʱ��
	time_t ValidDate;                //������Ч����
	time_t FirstVerifyTime;        // �״���֤ʱ��
	time_t EndTime;                 //���ܵ���ʱ��
	ULONG32	Time;					//����ʱ��   ��
	char Generator[255];             //������
	char SoftName[255];             //�����
	int Type;                    //��������
	char Device[255];			//�豸
	bool ban;				//���

public:
	const char* status_str();

	const char* type_str();

};
