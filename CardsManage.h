#pragma once
#include<stdio.h>
#include<mysql.h>
#include<vector>
#include"CardStruct.h"
class CardsManage
{
public:
	CardsManage();
	~CardsManage();
	static CardsManage* get_instance();

	bool connect(const char* host, int port, const char* user, const char* pass, const char* databaseName = "MyCards_Verify");
	int insert_card(const Card* p);
	int delete_card(const char* key);
	size_t query_where(std::vector<Card>& arr, const char* where_str = nullptr);
	size_t query_key(const char * key, Card& data);
	bool change_status(const char* key, CardStatus new_status);
	bool update_device(const char* key, const char* device);
	bool change_ban(const char* key, bool ban);
	bool check_time(Card& data);
	bool activate(Card &data);
private:
	const char* m_host;
	int			m_port;
	const char* m_user;
	const char* m_pass;
	const char* m_databaseName;
	MYSQL* m_pMysql;
	static CardsManage* m_this;
	void to_card(MYSQL_ROW row,Card& data);

};

