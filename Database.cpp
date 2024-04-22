#include "Database.hpp"

#include "Customers.hpp"
#include "Products.hpp"
#include "Orders.hpp"

#include <iostream>

//TODO FIX SPAGHETTI CODE, create seperate classes for each Table 


void Database::addDataIntoTable() //TODO implement validating user imput
{

	Environment* env = Environment::createEnvironment(); //TODO create method? Or maybe use RAII?

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456";
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	Connection* conn = env->createConnection(user, pass, constr);

	std::cout << "Which table do you want to add data to: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";
	TableType tableType{ static_cast<TableType>(userInterface.getInputNumber()) };

	switch (tableType) //TODO create factory method 
	{
	case TableType::CUSTOMERS:
		table = std::make_unique<Customers>();
		break;
	case TableType::PRODUCTS:
		table = std::make_unique<Products>();
		break;
	case TableType::ORDERS:
		table = std::make_unique<Orders>();
		break;
	default:
		std::cout << "Nothing" << std::endl; //TODO implement
	}

	table->addData(conn);

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::updateDataInTable() //TODO implement validating user imput
{
	Environment* env = Environment::createEnvironment(); //TODO create method? Or maybe use RAII?

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456";
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	Connection* conn = env->createConnection(user, pass, constr);

	std::cout << "Which table do you want to update data in: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";
	TableType tableType{ static_cast<TableType>(userInterface.getInputNumber()) };

	switch (tableType) //TODO create factory method
	{
	case TableType::CUSTOMERS:
		table = std::make_unique<Customers>();
		break;
	case TableType::PRODUCTS:
		table = std::make_unique<Products>();
		break;
	case TableType::ORDERS:
		table = std::make_unique<Orders>();
		break;
	default:
		std::cout << "Nothing" << std::endl; //TODO implement
	}

	table->updateData(conn);

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::deleteDataFromTable() //TODO implement validating user imput
{
	Environment* env = Environment::createEnvironment(); //TODO create method? Or maybe use RAII?

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456";
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	Connection* conn = env->createConnection(user, pass, constr);

	std::cout << "Enter ID that you want to remove: ";
	Id idToRemove{ userInterface.getInputNumber() };

	std::cout << "Which table do you want to delete data from: "
		<< "Customers - Press 0" << std::endl
		<< "Products - Press 1" << std::endl
		<< "Orders - Press 2" << std::endl
		<< "Your choice: ";
	TableType tableType{ static_cast<TableType>(userInterface.getInputNumber()) };

	switch (tableType) //TODO create factory method
	{
	case TableType::CUSTOMERS:
		table = std::make_unique<Customers>();
		break;
	case TableType::PRODUCTS:
		table = std::make_unique<Products>();
		break;
	case TableType::ORDERS:
		table = std::make_unique<Orders>();
		break;
	default:
		std::cout << "Nothing" << std::endl; //TODO implement
	}

	table->deleteData(conn, idToRemove);
	
	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::retrieveData(const std::unordered_set<std::string>& chosenColumns) //TODO implement exception handling
{
	Environment* env = Environment::createEnvironment();

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456";
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	Connection* conn = env->createConnection(user, pass, constr);

	table = std::make_unique<Customers>();
	table->retrieveData(conn);

	table = std::make_unique<Products>();
	table->retrieveData(conn);

	table = std::make_unique<Orders>();
	table->retrieveData(conn);

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::displayColumns() const
{
	//TODO implement displaying columns to choose
}

std::unordered_set<std::string> Database::chooseColumns() const
{
	return std::unordered_set<std::string>{}; //TODO implement choosing columns
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
		retrieveData(chooseColumns());
		break;
	default:
		std::cout << "nothing" << std::endl; //TODO implement logic 
	}
}