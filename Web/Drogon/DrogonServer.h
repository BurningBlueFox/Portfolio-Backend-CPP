#pragma once

#include <string>
#include "../IServer.h"
#include <drogon/drogon.h>
namespace ThiagoLeao::Portfolio::Web::Drogon
{
	class DrogonServer : public IServer
	{
	public:
		DrogonServer(std::string& ip, unsigned short port);
		void Run() override;
	private:
		std::string ip;
		unsigned short port;
	};
}