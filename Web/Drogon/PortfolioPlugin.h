#pragma once
#include <drogon/drogon.h>
using namespace drogon;
namespace ThiagoLeao::Portfolio::Web::Drogon
{
	class PortfolioPlugin : public drogon::Plugin<PortfolioPlugin>
	{
	public:
		void initAndStart(const Json::Value& config) override;
		void shutdown() override;
		std::string& GetPortfolio();
	private:
		std::string portfolio;
	};
}