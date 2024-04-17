#include "Database.hpp"
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
	Table table{ static_cast<Table>(userInterface.getInputNumber()) };

	switch (table)
	{
	case Table::CUSTOMERS:
		insertRow(conn, "CUSTOMERS");
		break;
	case Table::PRODUCTS:
		insertRow(conn, "PRODUCTS");
		break;
	case Table::ORDERS:
		insertRow(conn, "ORDERS");
		break;
	default:
		std::cout << "Nothing" << std::endl; //TODO implement
	}

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::insertRow(Connection* conn, std::string tableName) const
{
	std::cout << "Enter value for column 1: ";
	std::string value1{ userInterface.getInputWord() };

	std::cout << "Enter value for column 2: ";
	std::string value2{ userInterface.getInputWord() };

	std::cout << "Enter value for column 3: ";
	std::string value3{ userInterface.getInputWord() };

	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "INSERT INTO " + tableName + " VALUES('" + value1 + "', '" + value2 + "', '" + value3 + "')" }; //TODO check - is it ok to put '' around integer values?
	stmt->executeUpdate(sqlStatement); //TODO - should column names be provided?
	conn->terminateStatement(stmt);
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
	Table table{ static_cast<Table>(userInterface.getInputNumber()) };

	switch (table)
	{
	case Table::CUSTOMERS:
	{
		std::cout << "Enter ID that you want to update: ";
		std::string rowId{ userInterface.getInputWord() };

		std::cout << "Enter column name that you want to update: ";
		std::string columnName{ userInterface.getInputWord() };

		std::cout << "Enter value that you want to update it to: ";
		std::string newValue{ userInterface.getInputWord() };

		Statement* stmt = conn->createStatement();
		SqlStatement sqlStatement{ "UPDATE CUSTOMERS SET " + columnName + " = '" + newValue + "' WHERE CUSTOMER_ID = " + rowId }; //TODO check - is it ok to put '' around integer values?
		stmt->executeUpdate(sqlStatement);
		conn->terminateStatement(stmt);
		break;
	}
	case Table::PRODUCTS:
	{
		std::cout << "Enter ID that you want to update: ";
		std::string rowId{ userInterface.getInputWord() };

		std::cout << "Enter column name that you want to update: ";
		std::string columnName{ userInterface.getInputWord() };

		std::cout << "Enter value that you want to update it to: ";
		std::string newValue{ userInterface.getInputWord() };

		Statement* stmt = conn->createStatement();
		SqlStatement sqlStatement{ "UPDATE PRODUCTS SET " + columnName + " = '" + newValue + "' WHERE PRODUCT_ID = " + rowId }; //TODO check - is it ok to put '' around integer values?
		stmt->executeUpdate(sqlStatement);
		conn->terminateStatement(stmt);
		break;
	}
	case Table::ORDERS:
	{
		std::cout << "Enter ID that you want to update: ";
		std::string rowId{ userInterface.getInputWord() };

		std::cout << "Enter column name that you want to update: ";
		std::string columnName{ userInterface.getInputWord() };

		std::cout << "Enter value that you want to update it to: ";
		std::string newValue{ userInterface.getInputWord() };

		Statement* stmt = conn->createStatement();
		SqlStatement sqlStatement{ "UPDATE ORDERS SET " + columnName + " = '" + newValue + "' WHERE ORDERS_ID = " + rowId }; //TODO check - is it ok to put '' around integer values?
		stmt->executeUpdate(sqlStatement);
		conn->terminateStatement(stmt);
		break;
	}
	default:
		std::cout << "Nothing" << std::endl; //TODO implement
	}

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::updateRow(Connection* conn, std::string tableName) const
{
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
	Table table{ static_cast<Table>(userInterface.getInputNumber()) };

	switch (table)
	{
	case Table::CUSTOMERS:
		deleteRowIfPossible(conn, "CUSTOMERS", "CUSTOMER_ID", idToRemove);
		break;
	case Table::PRODUCTS:
		deleteRowIfPossible(conn, "PRODUCTS", "PRODUCT_ID", idToRemove);
		break;
	case Table::ORDERS:
		deleteRow(conn, "ORDERS", "ORDER_ID", idToRemove);
		break;
	default:
		std::cout << "Nothing" << std::endl; //TODO implement
	}
	
	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::deleteRowIfPossible(Connection* conn, std::string tableName, std::string columnName, Id idToRemove) const //TODO rethink this design, its not really OCP..
{
	Statement* stmt = conn->createStatement("SELECT " + columnName + " FROM ORDERS");
	ResultSet* rs = stmt->executeQuery();
	std::unordered_set<Id> idsFromOrders{};

	while (rs->next())
	{
		Id id = rs->getInt(1);
		idsFromOrders.insert(id);
	}

	if (idsFromOrders.find(idToRemove) == idsFromOrders.end())
	{
		deleteRow(conn, tableName, columnName, idToRemove);
	}
	else
	{
		std::cout << "You can't remove this id, it is present in orders" << std::endl;
	}

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);
}

void Database::deleteRow(Connection* conn, std::string tableName, std::string columnName, Id idToRemove) const
{
	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "DELETE FROM " + tableName + " WHERE " + columnName + " = " + std::to_string(idToRemove) };
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}


void Database::retrieveData(const std::unordered_set<std::string>& chosenColumns) //TODO implement exception handling
{
	Environment* env = Environment::createEnvironment();

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456";
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	Connection* conn = env->createConnection(user, pass, constr);

	SqlStatement sqlQueryForCustomers{ "SELECT CUSTOMER_ID, CUSTOMER_NAME, PHONE_NUMBER FROM CUSTOMERS" };
	displayTable(conn, sqlQueryForCustomers);

	SqlStatement sqlQueryForProducts{ "SELECT PRODUCT_ID, PRODUCT_NAME, PRICE_PER_UNIT FROM PRODUCTS" };
	displayTable(conn, sqlQueryForProducts);

	SqlStatement sqlQueryForOrders{ "SELECT ORDER_ID, CUSTOMER_ID, PRODUCT_ID FROM ORDERS" };
	displayTable(conn, sqlQueryForOrders);

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}

void Database::displayTable(Connection* conn, SqlStatement sqlQuery) const
{
	Statement* stmt = conn->createStatement();
	stmt->setSQL(sqlQuery);
	ResultSet* rs = stmt->executeQuery();

	std::cout << std::endl;

	while (rs->next())
	{
		std::cout << rs->getString(1) << " " << rs->getString(2) << " " << rs->getInt(3) << std::endl;
	}

	std::cout << std::endl;

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);
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