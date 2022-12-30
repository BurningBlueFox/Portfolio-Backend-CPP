#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include "../IDataSource.h"

namespace ThiagoLeao::Portfolio::Data::Json
{
	class JsonDataSource : IDataSource
	{
	public:
		JsonDataSource(std::ifstream& buffer);
		std::vector<std::shared_ptr<CareerProject>> GetCareerProjects() override;
		std::vector<std::shared_ptr<CareerExperience>> GetCareerExperiences() override;
	private:
		std::vector<std::shared_ptr<CareerExperience>> _vCareerExperience;
		std::vector<std::shared_ptr<CareerProject>> _vCareerProject;
		static std::chrono::year_month ConvertDate(const std::string& date);
		static void AddProject(const nlohmann::json::value_type& entry,
			std::vector<std::shared_ptr<CareerProject>>& vec);
		static void AddExperience(const nlohmann::json::value_type& entry,
			std::vector<std::shared_ptr<CareerExperience>>& vec,
			std::vector<std::shared_ptr<CareerProject>>& projs);
		static std::shared_ptr<CareerProject> FindProjById(int id, std::vector<std::shared_ptr<CareerProject>>& projects);
	};
}
