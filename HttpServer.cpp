#include"pch.h"
#include"HttpServer.h"
#include"CardsManage.h"
#include"json/include/nlohmann/json.hpp"
#include"help.h"
using std::string;

Server ser;
string notice;
void set_notice(string str)
{
	notice = str;
}

/*
* ·�ɴ���֮ǰ
*/
Server::HandlerResponse PreHandler(const Request& req, Response& res)
{


	/*
	* ����ҪЭ��
	*/
	//if (!req.has_header("Version") || !req.has_header("SoftName"))
	//{
	//	std::string  Context = "{\"status\": \"err\",\"data\":\"\"}";
	//	res.status = 500;
	//	//res.set_header(Context, "application/json");
	//	return Server::HandlerResponse::Handled;
	//}
	nlohmann::json json;
	if ( req.path.compare("/Activate")==0)
	{
		//�ж��Ƿ�ȱ�ٲ���
		if (!req.has_param("Key")|| !req.has_param("Device"))
		{
			json["status"] = card_server::missing_param;
			json["error"] = G2U("ȱ�ٲ���");
			res.status = OK_200;
			res.set_content(json.dump(), "application/json");
			return Server::HandlerResponse::Handled;
		}

	}
	else if (req.path.compare("/Query") == 0)
	{
		//�ж��Ƿ�ȱ�ٲ���
		if (!req.has_param("Key"))
		{
			json["status"] = card_server::missing_param;
			json["error"] = G2U("ȱ�ٲ���");
			res.status = OK_200;
			res.set_content(json.dump(), "application/json");
			return Server::HandlerResponse::Handled;
		}
	}

	return Server::HandlerResponse::Unhandled;
}
/*
* Activate ·��
*/
void router_activate(const Request& req, Response& res)
{
	res.status = OK_200;
	nlohmann::json json;


	Card data = { 0 };
	size_t i;
	Params::const_iterator pKey;
	Params::const_iterator pDevice;
	try
	{
		pKey = req.params.find("Key");
		//if (pKey->second.length() != 32)
		//{
		//	json["status"] = 402;
		//	json["error"] = G2U("��Ч����");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}

		pDevice = req.params.find("Device");
		//if (pDevice->second.length() != 32)
		//{
		//	json["status"] = 405;
		//	json["error"] = G2U("��Ч����");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}


		CardsManage* pManag = CardsManage::get_instance();
		i = pManag->query_key(pKey->second.c_str(), data);

		if (i == NULL)
		{//��ѯʧ��
			json["status"] = card_server::invalid_param;
			json["error"] = G2U("��Ч����");
			res.set_content(json.dump(), "application/json");
			return ;
		}
		//����Ƿ񱻷��
		if (data.ban)
		{
			json["status"] = card_server::card_ban;
			json["error"] = G2U("�ÿ����ѱ����");
			res.set_content(json.dump(), "application/json");
			return ;
		}
		switch (data.status)
		{
		case CardStatus::Activate:
			json["status"] = card_server::card_activate;
			json["error"] = G2U("�����ѱ�����!");
			res.set_content(json.dump(), "application/json");
			break;
		case CardStatus::nonActivated:
			strcpy_s(data.Device, pDevice->second.c_str());
			if (pManag->activate(data))
			{
				//����ɹ�
				json["status"] = 0;
				json["data"] = {
					{"status",data.status},
					{"Type",data.Type},
					{"FirstVerifyTime",data.FirstVerifyTime},
					{"EndTime",data.EndTime}
				};
			}
			else
			{
				//����ʧ��
				json["status"] = card_server::activate_fail;
				json["error"] = G2U("����ʧ��!");
			}
			res.set_content(json.dump(), "application/json");
			break;
		case CardStatus::Expired:

			json["status"] = card_server::card_expired;
			json["error"] = G2U("�����ѵ���!");
			res.set_content(json.dump(), "application/json");
			break;
		default:
			throw;
		}
	}
	catch (const std::exception& except)
	{
		res.status = 500;
		res.set_content("{\"status\":500\}", "application/json");
	}
	return ;
}
/*
* Query ·��
*/
void router_query(const Request& req, Response& res) {
	res.status = OK_200;
	nlohmann::json json;
	Card data = { 0 };
	size_t i;
	Params::const_iterator pKey;
	Params::const_iterator pDevice;
	try
	{


		pKey = req.params.find("Key");
		//if (pKey->second.length() != 32)
		//{
		//	json["status"] = 402;
		//	json["error"] = G2U("��Ч����");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}

		pDevice = req.params.find("Device");
		//if (pDevice->second.compare(data.Device) != 0)
		//{
		//	json["status"] = 405;
		//	json["error"] = G2U("��Ч����");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}


		CardsManage* pManag = CardsManage::get_instance();
		i = pManag->query_key(pKey->second.c_str(), data);
		if (i == NULL)
		{
			json["status"] = card_server::invalid_param;
			json["error"] = G2U("��Ч����");
			res.set_content(json.dump(), "application/json");
			return ;

		}
		//״̬���Ǵ���δ����,����֤�豸
		if ( data.status!= CardStatus::nonActivated  )
		{
			if (pDevice == req.params.end()|| pDevice->second.compare(data.Device) != 0)
			{
				json["status"] = card_server::missing_param;
				json["error"] = G2U("ȱ�ٲ���Device");
				res.set_content(json.dump(), "application/json");
				return;
			}


		
		}
		//�����Ƿ񱻷��
		if (data.ban)
		{
			json["status"] = card_server::card_ban;
			json["error"] = G2U("�ÿ����ѱ����");
			res.set_content(json.dump(), "application/json");
			return ;
		}
		


		//����һЩ��������
		json["status"] = 0;
		json["data"] = {
			{"Status",data.status},
			{"Type",data.Type},
			{"FirstVerifyTime",data.FirstVerifyTime},
			{"EndTime",data.EndTime},
		};

		json["error"] = "ok";
		res.set_content(json.dump(), "application/json");
	}
	catch (const std::exception& except)
	{
		res.status = 500;
		res.set_content("{\"status\":500\}", "application/json");
	}
	return ;
}
/*
* Notice ·��
*/
void router_notice(const Request& req, Response& res)
{
	try
	{
		res.status = OK_200;
		nlohmann::json json;
		json["status"] = card_server::ok;
		json["notice"] = G2U(notice);
		res.set_content(json.dump(), "application/json");
	}
	catch (const std::exception&)
	{
		nlohmann::json json;
		json["status"] = card_server::unknown;
		res.set_content(json.dump(), "application/json");
	}
}
bool check_invalid_params(const Request& req, Response& res)
{
	nlohmann::json json;


	Card data = { 0 };
	size_t i;
	Params::const_iterator pKey;
	Params::const_iterator pDevice;
	pKey = req.params.find("Key");
	if (pKey->second.length() != 32)
	{
		json["status"] = card_server::invalid_param;
		json["error"] = G2U("��Ч����");
		res.set_content(json.dump(), "application/json");
		return true;
	}

	pDevice = req.params.find("Device");
	if (pDevice->second.compare(data.Device) != 32)
	{
		json["status"] = card_server::invalid_param;

		json["error"] = G2U("��Ч����");
		res.set_content(json.dump(), "application/json");
		return true;
	}
	return false;
}
bool StartupServer()
{
	bool ok;


	ser.set_pre_routing_handler(PreHandler);

	/*
	* ����Ĭ����ӦЭ��ͷ
	*/
	Headers DefaultHeads = { {"Version","1.0"} };
	ser.set_default_headers(DefaultHeads);
	
	ser.Get("/Activate",router_activate);
	ser.Get("/Query", router_query);
	ser.Get("/Notice", router_notice);


	ok = ser.is_valid();
	ser.listen("0.0.0.0", 5050);
	return ok;
}