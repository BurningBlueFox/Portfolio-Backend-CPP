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
		std::string name;
		std::chrono::year_month startDate;
		std::chrono::year_month endDate;
		bool currentJob;
		std::vector<std::shared_ptr<CareerProject>> careerProjects;
		std::vector<ExternalLink> externalLinks;

		CareerExperience(const std::string& name,
			const std::chrono::year_month& startDate,
			const std::chrono::year_month& endDate,
			bool currentJob,
			const std::vector<std::shared_ptr<CareerProject>>& careerProjects)
			: name(name), startDate(startDate), endDate(endDate), currentJob(currentJob),
			  careerProjects(careerProjects)
		{
		}
	};
}