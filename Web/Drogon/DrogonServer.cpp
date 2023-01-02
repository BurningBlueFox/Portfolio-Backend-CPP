#include "DrogonServer.h"

#include <utility>
using namespace drogon;

namespace ThiagoLeao::Portfolio::Web::Drogon
{
	DrogonServer::DrogonServer(std::string& ip, unsigned short port) : ip(ip), port(port)
	{
		//DrogonServer::dataExport = std::move(portfolio);
	}

	void DrogonServer::Run()
	{
		isRunning = true;

		Json::Value plugins;
		Json::Value PortfolioPlugin;
		PortfolioPlugin["name"] = "ThiagoLeao::Portfolio::Web::Drogon::PortfolioPlugin";
		plugins["plugins"].insert(0, PortfolioPlugin);

		app().setLogPath("./")
			.setLogLevel(trantor::Logger::kWarn)
			.addListener(ip, port)
			.loadConfigJson(plugins)
			.setThreadNum(8)
			.run();
	}
	bool DrogonServer::IsRunning()
	{
		return isRunning;
	}

	void DrogonServer::Stop()
	{
		isRunning = false;
	}

}