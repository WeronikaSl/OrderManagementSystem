#include "Database.hpp"

#include "Customers.hpp"
#include "Products.hpp"
#include "Orders.hpp"
#include "TableFactory.hpp"

#include <iostream> 

void Database::addDataIntoTable()
{
	displayTableNames("Which table do you want to add data to: ");
	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->addData(databaseConnection.getConnection());
}

void Database::updateDataInTable()
{
	displayTableNames("Which table do you want to update data in: ");
	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->updateData(databaseConnection.getConnection());
}

void Database::deleteDataFromTable()
{
	std::cout << "Enter ID that you want to remove: ";
	Id idToRemove{ userInterface.getInputNumber() };

	displayTableNames("Which table do you want to delete data from: ");
	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->deleteData(databaseConnection.getConnection(), idToRemove);
}

void Database::retrieveData()
{
	displayTableNames("Which table do you want to retrive data from: ");
	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->retrieveData(databaseConnection.getConnection());
}

void Database::displayTableNames(std::string statament) const
{
	std::cout << statament << std::endl;

	for (int i{ 0 }; i < amountOfTableNames; ++i)
	{
		std::cout << tableNames[i] << " - press " << i << std::endl;
	}

	std::cout << "Your choice: ";
}

void Database::performOperation(DatabaseOpetation chosenOperation)
{
	switch (chosenOperation) {
	case DatabaseOpetation::ADD:
		addDataIntoTable();
		break;
	case DatabaseOpetation::UPDATE:
		updateDataInTable();
		break;
	case DatabaseOpetation::DELETE:
		deleteDataFromTable();
		break;
	case DatabaseOpetation::RETRIEVE:
		retrieveData();
		break;
	default:
		std::cout << "There's no such option" << std::endl;
	}
}

std::array<std::string, 4> Database::getOperationsNames() const
{
	return operationsNames;
}
