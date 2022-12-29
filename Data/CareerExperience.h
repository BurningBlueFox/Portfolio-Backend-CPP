#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "ExternalLink.h"
#include "CareerProject.h"
namespace ThiagoLeao::Portfolio::Data
{
	struct CareerExperience
	{
	public:
		int id;
		std::string name;
		std::vector<ExternalLink> externalLinks;
		std::vector<CareerProject> careerProjects;
		std::chrono::year_month startDate;
		std::chrono::year_month endDate;
	};
}