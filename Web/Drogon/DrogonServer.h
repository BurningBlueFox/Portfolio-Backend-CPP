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
		//static std::string dataExport;
		void Run() override;
		bool IsRunning() override;
		void Stop() override;
	private:
		std::string ip;
		unsigned short port;
		bool isRunning;
	};
}