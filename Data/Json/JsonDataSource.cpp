#include "JsonDataSource.h"
#include "JsonValues.h"
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;

namespace ThiagoLeao::Portfolio::Data::Json
{
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
		auto description = entry[KEY_DESCRIPTION].get<std::string>();
		auto date = ConvertDate(entry[KEY_PROJECT_DATE].get<std::string>());

		std::vector<ExternalLink> links;

		for (auto image : entry[KEY_IMAGES])
		{
			links.emplace_back(image.get<std::string>(), "", Image);
		}
		for (auto video : entry[KEY_VIDEOS])
		{
			links.emplace_back(video.get<std::string>(), "", YoutubeVideo);
		}
		for (auto link : entry[KEY_LINKS])
		{
			links.emplace_back(link[KEY_URL].get<std::string>(), link[KEY_DESCRIPTION].get<std::string>(), WebPage);
		}

		std::shared_ptr<CareerProject> cProj(new CareerProject(id, name, description, date));
		cProj->externalLinks = links;
		vec.emplace_back(std::move(cProj));
	}

	void JsonDataSource::AddExperience(const json::value_type& entry,
		std::vector<std::shared_ptr<CareerExperience>>& vec,
		std::vector<std::shared_ptr<CareerProject>>& projs)
	{
		auto name = entry[KEY_NAME].get<std::string>();
		auto desctiption = entry[KEY_DESCRIPTION].get<std::string>();
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

		std::shared_ptr<CareerExperience>
			cExp(new CareerExperience(name, desctiption, startDate, endDate, currentJob, proj));
		vec.emplace_back(std::move(cExp));
	}

	std::shared_ptr<CareerProject> JsonDataSource::FindProjById(int id,
		std::vector<std::shared_ptr<CareerProject>>& projects)
	{
		for (auto p : projects)
		{
			if (p->id == id)
				return p;
		}
		return nullptr;
	}
}