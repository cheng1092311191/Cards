#include "pch.h"

#include "CardStruct.h"

const char* Card::status_str()
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
const char* Card::type_str()
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
