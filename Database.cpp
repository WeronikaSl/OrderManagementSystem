#include "Database.hpp"
#include <iostream>

void Database::addData()
{
	std::cout << "Data added" << std::endl; //TODO implement logic 
}

void Database::updateData()
{
	std::cout << "Data updated" << std::endl; //TODO implement logic 
}

void Database::deleteData()
{
	std::cout << "Data removed" << std::endl; //TODO implement logic 
}

void Database::retrieveData()
{
	std::cout << "Data retrieved" << std::endl; //TODO implement logic 
}

void Database::performOperation(DatabaseOpetation operation)
{
	switch (operation) {
	case DatabaseOpetation::ADD:
		addData();
		break;
	case DatabaseOpetation::UPDATE:
		updateData();
		break;
	case DatabaseOpetation::DELETE:
		deleteData();
		break;
	case DatabaseOpetation::RETRIEVE:
		retrieveData();
		break;
	default:
		std::cout << "nothing" << std::endl; //TODO implement logic 
	}
}
