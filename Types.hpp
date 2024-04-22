#pragma once
#include <string>

enum class DatabaseOpetation {ADD, UPDATE, DELETE, RETRIEVE};

enum class TableType {CUSTOMERS, PRODUCTS, ORDERS};

using SqlStatement = std::string;
using Id = int;