#pragma once

#include <string>
namespace ThiagoLeao::Portfolio::Data
{
	enum LinkType
	{
		WebPage,
		Image,
		YoutubeVideo
	};

	struct ExternalLink
	{
	public:
		std::string url;
		std::string description;
		LinkType linkType;

		ExternalLink(const std::string& url, const std::string& description, LinkType linkType)
			: url(url), description(description), linkType(linkType)
		{
		}
	};
}