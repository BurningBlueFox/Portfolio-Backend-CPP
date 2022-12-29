#include <iostream>
#include "Data/Json/JsonDataSource.h"

using DataSource = ThiagoLeao::Portfolio::Data::Json::JsonDataSource;
int main()
{
	std::ifstream source("data.json");
	std::unique_ptr<DataSource> dataSource(new DataSource(source));

	source.close();
	return 0;
}
