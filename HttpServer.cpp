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
* 路由处理之前
*/
Server::HandlerResponse PreHandler(const Request& req, Response& res)
{


	/*
	* 检查必要协议
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
		//判断是否缺少参数
		if (!req.has_param("Key")|| !req.has_param("Device"))
		{
			json["status"] = card_server::missing_param;
			json["error"] = G2U("缺少参数");
			res.status = OK_200;
			res.set_content(json.dump(), "application/json");
			return Server::HandlerResponse::Handled;
		}

	}
	else if (req.path.compare("/Query") == 0)
	{
		//判断是否缺少参数
		if (!req.has_param("Key"))
		{
			json["status"] = card_server::missing_param;
			json["error"] = G2U("缺少参数");
			res.status = OK_200;
			res.set_content(json.dump(), "application/json");
			return Server::HandlerResponse::Handled;
		}
	}

	return Server::HandlerResponse::Unhandled;
}
/*
* Activate 路由
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
		//	json["error"] = G2U("无效参数");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}

		pDevice = req.params.find("Device");
		//if (pDevice->second.length() != 32)
		//{
		//	json["status"] = 405;
		//	json["error"] = G2U("无效参数");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}


		CardsManage* pManag = CardsManage::get_instance();
		i = pManag->query_key(pKey->second.c_str(), data);

		if (i == NULL)
		{//查询失败
			json["status"] = card_server::invalid_param;
			json["error"] = G2U("无效参数");
			res.set_content(json.dump(), "application/json");
			return ;
		}
		//检查是否被封禁
		if (data.ban)
		{
			json["status"] = card_server::card_ban;
			json["error"] = G2U("该卡密已被封禁");
			res.set_content(json.dump(), "application/json");
			return ;
		}
		switch (data.status)
		{
		case CardStatus::Activate:
			json["status"] = card_server::card_activate;
			json["error"] = G2U("卡密已被激活!");
			res.set_content(json.dump(), "application/json");
			break;
		case CardStatus::nonActivated:
			strcpy_s(data.Device, pDevice->second.c_str());
			if (pManag->activate(data))
			{
				//激活成功
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
				//激活失败
				json["status"] = card_server::activate_fail;
				json["error"] = G2U("激活失败!");
			}
			res.set_content(json.dump(), "application/json");
			break;
		case CardStatus::Expired:

			json["status"] = card_server::card_expired;
			json["error"] = G2U("卡密已到期!");
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
* Query 路由
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
		//	json["error"] = G2U("无效参数");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}

		pDevice = req.params.find("Device");
		//if (pDevice->second.compare(data.Device) != 0)
		//{
		//	json["status"] = 405;
		//	json["error"] = G2U("无效参数");
		//	res.set_content(json.dump(), "application/json");
		//	return true;
		//}


		CardsManage* pManag = CardsManage::get_instance();
		i = pManag->query_key(pKey->second.c_str(), data);
		if (i == NULL)
		{
			json["status"] = card_server::invalid_param;
			json["error"] = G2U("无效参数");
			res.set_content(json.dump(), "application/json");
			return ;

		}
		//状态不是处于未激活,则验证设备
		if ( data.status!= CardStatus::nonActivated  )
		{
			if (pDevice == req.params.end()|| pDevice->second.compare(data.Device) != 0)
			{
				json["status"] = card_server::missing_param;
				json["error"] = G2U("缺少参数Device");
				res.set_content(json.dump(), "application/json");
				return;
			}


		
		}
		//卡密是否被封禁
		if (data.ban)
		{
			json["status"] = card_server::card_ban;
			json["error"] = G2U("该卡密已被封禁");
			res.set_content(json.dump(), "application/json");
			return ;
		}
		


		//返回一些基本数据
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
* Notice 路由
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
		json["error"] = G2U("无效参数");
		res.set_content(json.dump(), "application/json");
		return true;
	}

	pDevice = req.params.find("Device");
	if (pDevice->second.compare(data.Device) != 32)
	{
		json["status"] = card_server::invalid_param;

		json["error"] = G2U("无效参数");
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
	* 设置默认响应协议头
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