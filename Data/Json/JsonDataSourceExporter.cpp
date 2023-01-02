#include "JsonDataSourceExporter.h"
#include "JsonValues.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ThiagoLeao::Portfolio::Data::Json
{
	JsonDataSourceExporter::JsonDataSourceExporter()
	= default;

	std::string JsonDataSourceExporter::Export(IDataSource& source)
	{
		json finalJson;
		json projectJson = GetAllProjects(source.GetCareerProjects());
		json experienceJson = GetAllExperiences(source.GetCareerExperiences());

		finalJson[KEY_CAREER_EXPERIENCE] = experienceJson;
		finalJson[KEY_CAREER_PROJECTS] = projectJson;
		return finalJson.dump(4);
	}

	json JsonDataSourceExporter::GetAllProjects(std::vector<std::shared_ptr<CareerProject>> projects)
	{
		json j = json::array();

		for (auto entry : projects)
		{
			json proj = json::object();
			proj[KEY_ID] = entry->id;
			proj[KEY_NAME] = entry->name;
			proj[KEY_PROJECT_DATE] = GetFormattedDate(entry->date);
			proj[KEY_DESCRIPTION] = entry->description;
			proj[KEY_IMAGES] = GetImages(entry->externalLinks);
			proj[KEY_VIDEOS] = GetVideos(entry->externalLinks);
			proj[KEY_LINKS] = GetLinks(entry->externalLinks);

			j.push_back(proj);
		}

		return j;
	}

	json JsonDataSourceExporter::GetAllExperiences(std::vector<std::shared_ptr<CareerExperience>> experiences)
	{
		json j = json::array();

		for (auto entry : experiences)
		{
			bool currentJob = entry->currentJob;
			json exp = json::object();
			exp[KEY_NAME] = entry->name;
			exp[KEY_EXPERIENCE_START_DATE] = GetFormattedDate(entry->startDate);
			if (!currentJob)
				exp[KEY_EXPERIENCE_END_DATE] = GetFormattedDate(entry->endDate);

			exp[KEY_EXPERIENCE_CURRENT_JOB] = currentJob;

			auto proj = json::array();
			for (auto p : entry->careerProjects)
			{
				proj.push_back(p->id);
			}
			exp[KEY_EXPERIENCE_PROJECTS] = proj;

			exp[KEY_DESCRIPTION] = entry->description;

			j.push_back(exp);
		}

		return j;
	}

	json JsonDataSourceExporter::GetImages(std::vector<ExternalLink> links)
	{
		json j = json::array();
		for (auto link : links)
		{
			if (link.linkType == Image)
			{
				j.push_back(link.url);
			}
		}
		return j;
	}

	json JsonDataSourceExporter::GetVideos(std::vector<ExternalLink> links)
	{
		json j = json::array();
		for (auto link : links)
		{
			if (link.linkType == YoutubeVideo)
			{
				j.push_back(link.url);
			}
		}
		return j;
	}

	json JsonDataSourceExporter::GetLinks(std::vector<ExternalLink> links)
	{
		json j = json::array();

		for (auto link : links)
		{
			if (link.linkType == WebPage)
			{
				auto obj = json::object();
				obj[KEY_URL] = link.url;
				obj[KEY_DESCRIPTION] = link.description;
				j.push_back(obj);
			}
		}
		return j;
	}

	std::string JsonDataSourceExporter::GetFormattedDate(std::chrono::year_month date)
	{
		int year = int(date.year());
		int month = date.month().operator unsigned int();
		std::string monthFormatted;
		if (month < 10)
		{
			monthFormatted = "0";
		}
		monthFormatted += std::to_string(month);
		return std::to_string(year) + "-" + monthFormatted;
	}

}