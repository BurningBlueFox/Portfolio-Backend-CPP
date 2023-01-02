#include <iostream>
#include "Data/IDataSource.h"
#include "Data/IDataSourceExporter.h"
#include "Data/Json/JsonDataSource.h"
#include "Data/Json/JsonDataSourceExporter.h"

using IDataSource = ThiagoLeao::Portfolio::Data::IDataSource;
using IDataSourceExporter = ThiagoLeao::Portfolio::Data::IDataSourceExporter;

using DataSource = ThiagoLeao::Portfolio::Data::Json::JsonDataSource;
using DataSourceExporter = ThiagoLeao::Portfolio::Data::Json::JsonDataSourceExporter;

int main()
{
	std::ifstream source("data.json");
	std::unique_ptr<IDataSource> dataSource(new DataSource(source));
	std::unique_ptr<IDataSourceExporter> dataSourceExporter(new DataSourceExporter());

	std::cout << dataSourceExporter->Export(*dataSource);

	source.close();
	return 0;
}
