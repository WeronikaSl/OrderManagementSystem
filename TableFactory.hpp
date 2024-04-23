#pragma once

#include "Table.hpp"
#include "Types.hpp"

#include <memory>

class TableFactory
{
public:
	static std::unique_ptr<Table> getTable(TableType);
};