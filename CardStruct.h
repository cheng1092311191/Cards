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
	const char* status_str()
	{
		if (ban)
		{
			return "�����";
		}
		switch (status)
		{
		case CardStatus::nonActivated:
			return "δ����";
		case CardStatus::Activate:
			return "��ʹ��";
		case CardStatus::Expired:
			return "�ѵ���";
		default:
			return "δ֪";
		}
	}
	const char* type_str()
	{
		switch (Type)
		{
		case CardType::VPI:
			return "��Ա��";
		case CardType::Refill:
			return "��ֵ��";
		case CardType::Test:
			return "���Կ�";
		default:
			return "δ֪";
		}
	}
};
