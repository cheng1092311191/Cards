#pragma once
#include"CardsManage.h"
#include<vector>
#include<string>
#define    CARD_KEY_MAX       255
#define    CARD_DEVICE_MAX    255
#define	   CARD_CONFIG_FILE	"Config.ini"

// GBK字符串转成json识别的UTF8字符串
std::string G2U(const std::string& gbk);
std::string U2G(const std::string& utf8);
int MakeKey32(char* Buff);

int AddPage(CTabCtrl& Tab, const char* text, CDialogEx& Page, UINT nID, int nImage=-1);
bool ShowPage(CTabCtrl& Tab);

void Time2str(time_t time, CString& Buf);
int MakeCards(std::vector<Card>& arr, int Num, CardType Type, ULONG32 Time,  const char* Generator);
void handle_event();
CardStatus comb_i2status(int i);
CardType comb_i2type(int i);


