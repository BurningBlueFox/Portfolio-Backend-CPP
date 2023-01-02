#include <iostream>
#include "Data/IDataSource.h"
#include "Data/IDataSourceExporter.h"
#include "Data/Json/JsonDataSource.h"
#include "Data/Json/JsonDataSourceExporter.h"
#include "Web/IServer.h"
#include "Web/Drogon/DrogonServer.h"

using IDataSource = ThiagoLeao::Portfolio::Data::IDataSource;
using IDataSourceExporter = ThiagoLeao::Portfolio::Data::IDataSourceExporter;

using DataSource = ThiagoLeao::Portfolio::Data::Json::JsonDataSource;
using DataSourceExporter = ThiagoLeao::Portfolio::Data::Json::JsonDataSourceExporter;

using IServer = ThiagoLeao::Portfolio::Web::IServer;
using IpPort = ThiagoLeao::Portfolio::Web::IpPort;

using Server = ThiagoLeao::Portfolio::Web::Drogon::DrogonServer;

int main()
{
	std::ifstream source("data.json");
	std::unique_ptr<IDataSource> dataSource(new DataSource(source));
	source.close();

	std::unique_ptr<IDataSourceExporter> dataSourceExporter(new DataSourceExporter());

	std::cout << dataSourceExporter->Export(*dataSource); //Debug

	IpPort ipPort(0, 0, 0, 0, 80);
	std::string ip = ipPort.IpToString();
	std::unique_ptr<IServer> server(new Server(ip, ipPort.port));

	server->Run();

	return 0;
}
