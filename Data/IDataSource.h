#pragma once

#include <vector>
#include "CareerExperience.h"
#include "CareerProject.h"
namespace ThiagoLeao::Portfolio::Data
{
	class IDataSource
	{
	public:
		virtual std::vector<CareerProject> GetCareerProjects() = 0;
		virtual std::vector<CareerExperience> GetCareerExperiences() = 0;
	};
}