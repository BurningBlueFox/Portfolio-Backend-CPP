#pragma once

namespace ThiagoLeao::Portfolio::Web
{
	struct IpPort
	{
	public:
		char ip1, ip2, ip3, ip4;
		unsigned short port;

		IpPort(char ip1, char ip2, char ip3, char ip4, unsigned short port) :
			ip1(ip1), ip2(ip2), ip3(ip3), ip4(ip4), port(port)
		{
		}
		std::string IpToString()
		{
			char separator = ':';
			return std::to_string((int)ip1) + separator
				+ std::to_string((int)ip2) + separator
				+ std::to_string((int)ip3) + separator
				+ std::to_string((int)ip4);
		}
	};

	class IServer
	{
	public:
		virtual void Run() = 0;
	};
}