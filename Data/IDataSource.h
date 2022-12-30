#pragma once

#include <vector>
#include "CareerExperience.h"
#include "CareerProject.h"
namespace ThiagoLeao::Portfolio::Data
{
	class IDataSource
	{
	public:
		virtual std::vector<std::shared_ptr<CareerProject>> GetCareerProjects() = 0;
		virtual std::vector<std::shared_ptr<CareerExperience>> GetCareerExperiences() = 0;
	};
}