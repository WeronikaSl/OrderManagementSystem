#pragma once

#include "Types.hpp"
#include "UserInterface.hpp"

#include <array>
#include <vector>
#include <string>
#include <unordered_set>

#include <occi.h>

using namespace oracle::occi;

class Database
{
private:
	UserInterface userInterface;

	void addDataIntoTable(); 
	void insertRow(Connection*, std::string) const;
	void updateDataInTable();
	void updateRow(Connection*, std::string) const;
	void deleteDataFromTable();
	void deleteRowIfPossible(Connection*, std::string, std::string, Id) const;
	void deleteRow(Connection*, std::string, std::string, Id) const;
	void retrieveData(const std::unordered_set<std::string>&); //TODO check if you dont prevent copy elision here
	void displayTable(Connection*, SqlStatement) const;
	void displayColumns() const;
	std::unordered_set<std::string> chooseColumns() const;

public:
	void performOperation(DatabaseOpetation);
};