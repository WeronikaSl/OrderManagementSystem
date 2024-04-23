#include "Database.hpp"

#include "Customers.hpp"
#include "Products.hpp"
#include "Orders.hpp"
#include "TableFactory.hpp"

#include <iostream> 

void Database::addDataIntoTable() //TODO implement validating user imput
{
	std::cout << "Which table do you want to add data to: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";

	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->addData(databaseConnection.getConnection());
}

void Database::updateDataInTable() //TODO implement validating user imput
{
	std::cout << "Which table do you want to update data in: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";

	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->updateData(databaseConnection.getConnection());
}

void Database::deleteDataFromTable() //TODO implement validating user imput
{
	std::cout << "Enter ID that you want to remove: ";
	Id idToRemove{ userInterface.getInputNumber() };

	std::cout << "Which table do you want to delete data from: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";

	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->deleteData(databaseConnection.getConnection(), idToRemove);
}

void Database::retrieveData() //TODO implement exception handling
{
	std::cout << "Which table do you want to retrive data from: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";

	table = TableFactory::getTable(static_cast<TableType>(userInterface.getInputNumber()));
	table->retrieveData(databaseConnection.getConnection());
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
		std::cout << "nothing" << std::endl; //TODO implement logic 
	}
}

std::array<std::string, 4> Database::getOperationsNames() const
{
	return operationsNames;
}
