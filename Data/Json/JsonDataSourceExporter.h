#pragma once

#include "../IDataSourceExporter.h"
#include "nlohmann/json.hpp"
namespace ThiagoLeao::Portfolio::Data::Json
{
	class JsonDataSourceExporter : public IDataSourceExporter
	{
	public:
		JsonDataSourceExporter();
		std::string Export(IDataSource& source) override;
	private:
		nlohmann::json GetAllProjects(std::vector<std::shared_ptr<CareerProject>> projects);
		nlohmann::json GetAllExperiences(std::vector<std::shared_ptr<CareerExperience>> experiences);
		nlohmann::json GetImages(std::vector<ExternalLink> links);
		nlohmann::json GetVideos(std::vector<ExternalLink> links);
		nlohmann::json GetLinks(std::vector<ExternalLink> links);
		std::string GetFormattedDate(std::chrono::year_month date);

	};
}