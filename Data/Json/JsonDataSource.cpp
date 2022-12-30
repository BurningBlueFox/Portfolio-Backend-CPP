#include "JsonDataSource.h"
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;

namespace ThiagoLeao::Portfolio::Data::Json
{
	const std::string KEY_CAREER_PROJECTS = "CareerProjects";
	const std::string KEY_PROJECT_DATE = "Date";

	const std::string KEY_CAREER_EXPERIENCE = "CareerExperiences";
	const std::string KEY_EXPERIENCE_START_DATE = "StartDate";
	const std::string KEY_EXPERIENCE_END_DATE = "EndDate";
	const std::string KEY_EXPERIENCE_CURRENT_JOB = "CurrentJob";
	const std::string KEY_EXPERIENCE_PROJECTS = "Projects";

	const std::string KEY_NAME = "Name";
	const std::string KEY_ID = "Id";
	const std::string KEY_IMAGES = "Images";
	const std::string KEY_VIDEOS = "Videos";
	const std::string KEY_LINKS = "Links";

	JsonDataSource::JsonDataSource(std::ifstream& buffer)
	{
		json data = json::parse(buffer);

		for (const auto& entry : data[KEY_CAREER_PROJECTS])
		{
			AddProject(entry, _vCareerProject);
		}

		for (const auto& entry : data[KEY_CAREER_EXPERIENCE])
		{
			AddExperience(entry, _vCareerExperience, _vCareerProject);
		}

		std::cout << _vCareerProject.size() << " : " << _vCareerExperience.size() << std::endl;
	}

	std::vector<std::shared_ptr<CareerProject>> JsonDataSource::GetCareerProjects()
	{
		return _vCareerProject;
	}

	std::vector<std::shared_ptr<CareerExperience>> JsonDataSource::GetCareerExperiences()
	{
		return _vCareerExperience;
	}

	std::chrono::year_month JsonDataSource::ConvertDate(const std::string& date)
	{
		int year = std::stoi(date.substr(0, 4));
		int month = std::stoi(date.substr(5, 2));

		std::chrono::year y(year);
		std::chrono::month m(month);

		return { y, m };
	}

	void JsonDataSource::AddProject(const json::value_type& entry,
		std::vector<std::shared_ptr<CareerProject>>& vec)
	{
		auto id = entry[KEY_ID].get<int>();
		auto name = entry[KEY_NAME].get<std::string>();
		auto date = ConvertDate(entry[KEY_PROJECT_DATE].get<std::string>());

		std::shared_ptr<CareerProject> cProj(new CareerProject(id, name, date));
		vec.emplace_back(std::move(cProj));
	}

	void JsonDataSource::AddExperience(const json::value_type& entry,
		std::vector<std::shared_ptr<CareerExperience>>& vec,
		std::vector<std::shared_ptr<CareerProject>>& projs)
	{
		auto name = entry[KEY_NAME].get<std::string>();
		auto startDate = ConvertDate(entry[KEY_EXPERIENCE_START_DATE].get<std::string>());
		auto currentJob = entry[KEY_EXPERIENCE_CURRENT_JOB].get<bool>();
		std::chrono::year_month endDate{};

		if (!currentJob)
		{
			endDate = ConvertDate(entry[KEY_EXPERIENCE_END_DATE].get<std::string>());
		}

		std::vector<std::shared_ptr<CareerProject>> proj{};
		for (const auto& p : entry[KEY_EXPERIENCE_PROJECTS])
		{
			int projNumber = p.get<int>();
			auto projPtr = FindProjById(projNumber, projs);
			proj.emplace_back(projPtr);
		}

		std::shared_ptr<CareerExperience> cExp(new CareerExperience(name, startDate, endDate, currentJob, proj));
		vec.emplace_back(std::move(cExp));
	}

	std::shared_ptr<CareerProject> JsonDataSource::FindProjById(int id, std::vector<std::shared_ptr<CareerProject>>& projects)
	{
		for (auto p : projects)
		{
			if (p->id == id)
				return p;
		}
		return nullptr;
	}
}