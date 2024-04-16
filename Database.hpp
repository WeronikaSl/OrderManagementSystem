#pragma once

#include "Types.hpp"
#include "UserInterface.hpp"

#include <array>
#include <vector>
#include <string>
#include <unordered_set>

class Database
{
private:
	UserInterface userInterface;

	void addData(); 
	void updateData();
	void deleteData();
	void retrieveData(const std::unordered_set<std::string>&); //TODO check if you dont prevent copy elision here
	void displayColumns() const;
	std::unordered_set<std::string> chooseColumns() const;

public:
	void performOperation(DatabaseOpetation);
};