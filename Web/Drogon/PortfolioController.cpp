#include "PortfolioController.h"
#include "DrogonServer.h"
#include "PortfolioPlugin.h"

namespace ThiagoLeao::Portfolio::Web::Drogon
{

	void PortfolioController::asyncHandleHttpRequest(const HttpRequestPtr& req,
		std::function<void(const HttpResponsePtr&)>&& callback)
	{
		auto *pluginPtr=app().getPlugin<PortfolioPlugin>();

		auto resp = HttpResponse::newHttpResponse();
		resp->setStatusCode(k200OK);
		resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
		resp->setBody(pluginPtr->GetPortfolio());
		callback(resp);
	}
}