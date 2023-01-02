#include <iostream>

#include "Web/IServer.h"
#include "Web/Drogon/DrogonServer.h"



using IServer = ThiagoLeao::Portfolio::Web::IServer;
using IpPort = ThiagoLeao::Portfolio::Web::IpPort;

using Server = ThiagoLeao::Portfolio::Web::Drogon::DrogonServer;

int main()
{
	IpPort ipPort(127, 0, 0, 1, 80);
	std::string ip = ipPort.IpToString();
	std::shared_ptr<IServer> server(new Server(ip, ipPort.port));

	server->Run();

	return 0;
}
