#include "DrogonServer.h"
using namespace drogon;

namespace ThiagoLeao::Portfolio::Web::Drogon
{
	DrogonServer::DrogonServer(std::string& ip, unsigned short port) : ip(ip), port(port)
	{
	}

	void DrogonServer::Run()
	{
		app().setLogPath("./")
			.setLogLevel(trantor::Logger::kWarn)
			.addListener(ip, port)
			.setThreadNum(8)
			.enableRunAsDaemon()
			.run();
	}

}