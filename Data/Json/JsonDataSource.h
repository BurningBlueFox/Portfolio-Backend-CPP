#pragma once

#include <fstream>
#include "../IDataSource.h"
namespace ThiagoLeao::Portfolio::Data::Json
{
	class JsonDataSource : IDataSource
	{
	public:
		JsonDataSource(std::ifstream& buffer);
		std::vector<CareerProject> GetCareerProjects() override;
		std::vector<CareerExperience> GetCareerExperiences() override;
	private:
		std::vector<CareerExperience> _vCareerExperience;
		std::vector<CareerProject> _vCareerProject;
		static std::chrono::year_month ConvertDate(const std::string& date);
	};
}
