#include "Database.hpp"
#include <iostream>

void Database::addData(const std::unordered_set<std::string>& chosenColumns)
{
	std::cout << "Data added" << std::endl; //TODO implement logic 
}

void Database::updateData(const std::unordered_set<std::string>& chosenColumns)
{
	std::cout << "Data updated" << std::endl; //TODO implement logic 
}

void Database::deleteData(const std::unordered_set<std::string>& chosenColumns)
{
	std::cout << "Data removed" << std::endl; //TODO implement logic 
}

void Database::retrieveData(const std::unordered_set<std::string>& chosenColumns)
{
	std::cout << std::endl;
	iterateThroughTable(products, chosenColumns);
	std::cout << std::endl;
	iterateThroughTable(customers, chosenColumns);
	std::cout << std::endl;
	iterateThroughTable(orders, chosenColumns);
	std::cout << std::endl;
}

void Database::iterateThroughTable(std::array<std::vector<std::string>, 3> table, const std::unordered_set<std::string>& chosenColumns) const
{
	for (const auto& column : table)
	{
		if (chosenColumns.find(column[0]) != chosenColumns.end())
		{
			for (const auto& elem : column)
			{
				std::cout << elem << std::endl;
			}
			std::cout << std::endl;
		}
	}
}

void Database::displayColumns() const
{
	std::cout << std::endl << "PRODUCTS: " << std::endl;
	for (const auto& column : products)
	{
		std::cout << column[0] << std::endl;
	}

	std::cout << std::endl << "CUSTOMERS: " << std::endl;
	for (const auto& column : customers)
	{
		std::cout << column[0] << std::endl;
	}

	std::cout << std::endl << "ORDERS: " << std::endl;
	for (const auto& column : orders)
	{
		std::cout << column[0] << std::endl;
	}
}

std::unordered_set<std::string> Database::chooseColumns() const
{
	std::cout << "How many columns do you want to choose: ";
	int amountOfColumns{ userInterface.getInputNumber() };

	std::cout << std::endl << "Columns: " << std::endl;
	displayColumns();

	std::cout << std::endl;

	std::unordered_set<std::string> columns{}; //TODO change to std::array? max nr of columns is known
	std::string columnName{};

	for (int i{ 0 }; i < amountOfColumns; ++i)
	{
		std::cout << "Enter name of column nr " << i << ": ";
		std::cin >> columnName;
		columns.insert(columnName);
	}
	return columns;
}

void Database::performOperation(DatabaseOpetation chosenOperation)
{
	switch (chosenOperation) {
	case DatabaseOpetation::ADD:
		addData(chooseColumns());
		break;
	case DatabaseOpetation::UPDATE:
		updateData(chooseColumns());
		break;
	case DatabaseOpetation::DELETE:
		deleteData(chooseColumns());
		break;
	case DatabaseOpetation::RETRIEVE:
		retrieveData(chooseColumns());
		break;
	default:
		std::cout << "nothing" << std::endl; //TODO implement logic 
	}
}