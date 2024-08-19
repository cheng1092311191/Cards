#include "pch.h"

#include "CardStruct.h"

const char* Card::status_str()
{
	if (ban)
	{
		return "被封禁";
	}
	switch (status)
	{
	case CardStatus::nonActivated:
		return "未激活";
	case CardStatus::Activate:
		return "已使用";
	case CardStatus::Expired:
		return "已到期";
	default:
		return "未知";
	}
}
const char* Card::type_str()
{
	switch (Type)
	{
	case CardType::VPI:
		return "会员卡";
	case CardType::Refill:
		return "充值卡";
	case CardType::Test:
		return "测试卡";
	default:
		return "未知";
	}
}
