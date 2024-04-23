#pragma once

#include "Types.hpp"
#include "UserInterface.hpp"
#include "Table.hpp"
#include "DatabaseConnection.hpp"

#include <array>
#include <string>
#include <memory>

#include <occi.h>

using namespace oracle::occi;

class Database
{
private:
	DatabaseConnection databaseConnection;
	UserInterface userInterface;
	std::unique_ptr<Table> table{ nullptr };
	static constexpr int amountOfOperationsNames{ 4 };
	std::array<std::string, amountOfOperationsNames> operationsNames{ "Add data" , "Update data" , "Delete data" , "Retrieve data" };
	static constexpr int amountOfTableNames{ 3 };
	std::array<std::string, amountOfTableNames> tableNames{ "Customers", "Products", "Orders" };

	void addDataIntoTable(); 
	void updateDataInTable();
	void deleteDataFromTable();
	void retrieveData();

public:
	void performOperation(DatabaseOpetation);
	std::array<std::string, amountOfOperationsNames> getOperationsNames() const;
};