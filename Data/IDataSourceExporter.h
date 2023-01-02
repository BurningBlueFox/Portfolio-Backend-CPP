#pragma once

#include "IDataSource.h"
namespace ThiagoLeao::Portfolio::Data
{
	class IDataSourceExporter
	{
	public:
		virtual std::string Export(IDataSource& source) = 0;
	};
}