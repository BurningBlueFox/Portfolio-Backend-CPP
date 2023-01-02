#pragma once
#include <drogon/drogon.h>
using namespace drogon;

namespace ThiagoLeao::Portfolio::Web::Drogon
{
	class PortfolioController : public drogon::HttpSimpleController<PortfolioController>
	{
	public:
		void asyncHandleHttpRequest(const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback) override;

		PATH_LIST_BEGIN
			PATH_ADD("/portfolio", Get);
		PATH_LIST_END
	};
}
