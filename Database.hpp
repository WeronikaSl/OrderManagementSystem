#pragma once

#include "Types.hpp"
#include "UserInterface.hpp"
#include "Table.hpp"

#include <array>
#include <vector>
#include <string>
#include <unordered_set>
#include <memory>

#include <occi.h>

using namespace oracle::occi;

class Database
{
private:
	UserInterface userInterface;
	std::unique_ptr<Table> table{ nullptr };

	void addDataIntoTable(); 
	void updateDataInTable();
	void deleteDataFromTable();
	void retrieveData(const std::unordered_set<std::string>&); //TODO check if you dont prevent copy elision here
	void displayColumns() const;
	std::unordered_set<std::string> chooseColumns() const;

public:
	void performOperation(DatabaseOpetation);
};