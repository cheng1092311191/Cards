#include"pch.h"
#include "CardsManage.h"

#pragma comment(lib,"libmysql.lib")
#pragma warning(disable:4996)

CardsManage* CardsManage::m_this = nullptr;
CardsManage::CardsManage()
{
	m_host = "localhost";
	m_port = 3306;
	m_user = "root";
	m_pass = "";
	m_databaseName = "MyCards_Verify";
	m_pMysql = nullptr;
}

CardsManage::~CardsManage()
{
	if (m_pMysql)
	{
		mysql_close(m_pMysql);
		m_pMysql = nullptr;
	}
}



CardsManage* CardsManage::get_instance()
{
	return m_this;
}
bool CardsManage::connect(const char* host, int port, const char* user, const char* pass, const char* databaseName)
{
	m_host = host;
	m_port = port;
	m_user = user;
	m_pass = pass;
	m_databaseName = databaseName;
	m_pMysql = mysql_init(m_pMysql);
	if (!mysql_real_connect(m_pMysql, m_host, m_user, m_pass, NULL, m_port, NULL, NULL))
	{
		return false ;
	}
	mysql_set_character_set(m_pMysql, "gbk");
	/*
	* 创建数据库
	*/
	char buff[1024] = { 0 };
	sprintf_s(buff, "CREATE DATABASE %s;", m_databaseName);
	int i = mysql_query(m_pMysql, buff);
	/*
	* 选择数据库
	*/
	sprintf_s(buff, "USE %s;", m_databaseName);
	mysql_query(m_pMysql, buff);

	/*
	* 创建表
	*/
	i = mysql_query(m_pMysql, "CREATE TABLE Cards(\
		card_status int,\
		card_key CHAR(255) NOT NULL UNIQUE,\
		card_MakeDate BIGINT,\
		card_ValidDate BIGINT,\
		card_FirstVerifyTime BIGINT,\
		card_EndTime BIGINT,\
		card_TimeType INT,\
		card_Generator CHAR(255),\
		card_SoftName CHAR(255),\
		card_Type INT,\
		card_Device CHAR(255),\
		card_Ban INT\
		);"
	);
	m_this = this;
	return true;
}

/*
* 插入条记录
*/
int CardsManage::insert_card(const Card * p)
{
	char buff[1024] = { 0 };
	sprintf_s(buff, "insert into Cards values(%d,'%s',%lld,%lld,%lld,%lld,%d,'%s','%s',%d,'%s',%d);",
		p->status, p->key, p->MakeDate, p->ValidDate, p->FirstVerifyTime, 
		p->EndTime, p->Time, p->Generator, p->SoftName, p->Type, p->Device,
		p->ban
		);
	return mysql_query(m_pMysql, buff);
}
/*
* 删除条记录
*/
int CardsManage::delete_card(const char* key)
{
	char buff[1024] = { 0 };
	sprintf_s(buff, "delete from Cards where %d;");

	return mysql_query(m_pMysql, buff);
}

/*
* 查询
*/
size_t CardsManage::query_where(std::vector<Card>& arr,const char * where_str)
{
	arr.clear();
	ULONG i = 0;
	char buf[1024] = { 0 };
	if (where_str==NULL||strlen(where_str)==0)
	{
		sprintf_s(buf, "SELECT * FROM Cards;" );
	}
	else
	{
		sprintf_s(buf, "SELECT * FROM Cards WHERE %s;", where_str);
	}


	if (mysql_query(m_pMysql, buf))
	{
		return 0;
	}
	MYSQL_RES* res =  mysql_store_result(m_pMysql);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		Card data = { 0 };
		to_card(row, data);
		check_time(data);

		arr.push_back(data);
	}
	mysql_free_result(res);
	return arr.size();
}
/*
* 查询key
*/
size_t CardsManage::query_key(const char* key,Card &data)
{
	char buf[1024] = { 0 };
	sprintf_s(buf, "SELECT * FROM cards WHERE card_key='%s';", key);
	int status  = mysql_query(m_pMysql, buf);
	if (status !=0)
	{
		//失败
		return 0;
	}
	MYSQL_RES* res = mysql_store_result(m_pMysql);
	if (!res)
	{
		return 0;
	}
	size_t num = res->row_count;
	if (!num)
	{
		return 0;
	}

	MYSQL_ROW row =  mysql_fetch_row(res);
	to_card(row, data);
	//检查,更新
	check_time(data);

	mysql_free_result(res);
	return num;
}

/*
* 修改状态
*/
bool CardsManage::change_status(const char* key,CardStatus new_status)
{
	char buf[1024] = { 0 };
	sprintf_s(buf, "UPDATE Cards SET card_status=%d WHERE card_key='%s';",  new_status, key);
	return !mysql_query(m_pMysql, buf);
}


bool CardsManage::update_device(const char* key, const char* new_device)
{
	char buf[1024] = { 0 };
	sprintf_s(buf, "UPDATE Cards SET card_device='%s' WHERE card_key='%s';", new_device, key);
	return !mysql_query(m_pMysql, buf);
}
bool CardsManage::change_ban(const char* key, bool ban)
{
	char buf[1024] = { 0 };
	sprintf_s(buf, "UPDATE Cards SET card_ban=%d WHERE card_key='%s';", ban, key);
	return !mysql_query(m_pMysql, buf);
}
/*
	* 检查是否超时,并更新状态
	*/
bool CardsManage::check_time(Card& data)
{	
	if (data.status == CardStatus::Activate)
	{
		time_t	curtime = time(NULL);
		if (curtime >= data.EndTime)
		{
			/*
			* 更新状态
			*/
			int i = change_status(data.key, CardStatus::Expired);
			if (i==0)
			{
				data.status = CardStatus::Expired;
				return true;
			}

		}

	}
	return false;
}
/*
* 激活卡密
*	必须要设置key,device,time 成员
*/
bool CardsManage::activate(Card& data)
{

	time_t curtime = time(NULL);
	time_t endtime = curtime + data.Time;
	char buf[1024] = { 0 };
	sprintf_s(buf, "UPDATE Cards SET card_status=%d,card_FirstVerifyTime=%lld,card_endtime=%lld,card_device='%s' WHERE card_key='%s';", CardStatus::Activate, curtime,endtime,data.Device ,data.key);
	int i = mysql_query(m_pMysql, buf);
	if (i==0)
	{
		data.FirstVerifyTime = curtime;
		data.EndTime = endtime;
		return true;
	}
	return false;
}


/*
* 转成card 结构
*/
void CardsManage::to_card(MYSQL_ROW row,Card &data)
{
	/*
		card_status int,\
		card_key CHAR(255) NOT NULL UNIQUE,\
		card_MakeDate BIGINT,\
		card_ValidDate BIGINT,\
		card_FirstVerifyTime BIGINT,\
		card_EndTime BIGINT,\
		card_TimeType INT,\
		card_Generator CHAR(255),\
		card_SoftName CHAR(255),\
		card_Type INT,\
		card_Device CHAR(255),\
		card_IsBindDevice INT\
	*/
	data.status = atoi(row[0]);
	strcpy(data.key, row[1]);
	data.MakeDate = atoll(row[2]);
	data.ValidDate = atoll(row[3]);
	data.FirstVerifyTime = atoll(row[4]);
	data.EndTime = atoll(row[5]);
	data.Time = atoi(row[6]);
	strcpy(data.Generator, row[7]);
	strcpy(data.SoftName, row[8]);
	data.Type = atoi(row[9]);
	strcpy(data.Device,row[10]);
	data.ban = atoi(row[11]);
}
