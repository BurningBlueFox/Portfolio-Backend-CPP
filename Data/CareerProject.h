#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "ExternalLink.h"
namespace ThiagoLeao::Portfolio::Data
{
	struct CareerProject
	{
	public:
		int id;
		std::string name;
		std::chrono::year_month date;
		std::vector<ExternalLink> externalLinks;

		CareerProject(int id,
			const std::string& name,
			const std::chrono::year_month& date) : id(id), name(name), date(date)
		{
		}
	};
}