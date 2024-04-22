#include "Customers.hpp"

#include "Types.hpp"

#include <iostream>
#include <unordered_set>

void Customers::addData(Connection* conn) const
{
	std::cout << "Enter value for column 1: ";
	std::string value1{ userInterface.getInputWord() };

	std::cout << "Enter value for column 2: ";
	std::string value2{ userInterface.getInputWord() };

	std::cout << "Enter value for column 3: ";
	std::string value3{ userInterface.getInputWord() };

	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "INSERT INTO CUSTOMERS VALUES('" + value1 + "', '" + value2 + "', '" + value3 + "')" }; //TODO check - is it ok to put '' around integer values?
	stmt->executeUpdate(sqlStatement); //TODO - should column names be provided?
	conn->terminateStatement(stmt);
}

void Customers::updateData(Connection* conn) const
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
}

void Customers::deleteData(Connection* conn, Id idToRemove) const
{
	Statement* stmt = conn->createStatement("SELECT CUSTOMER_ID FROM ORDERS"); //TODO ?? maybe orders can has a method that will return ids?
	ResultSet* rs = stmt->executeQuery();
	std::unordered_set<Id> idsFromOrders{}; 

	while (rs->next())
	{
		Id id = rs->getInt(1);
		idsFromOrders.insert(id);
	}

	if (idsFromOrders.find(idToRemove) == idsFromOrders.end())
	{
		Statement* stmt = conn->createStatement();
		SqlStatement sqlStatement{ "DELETE FROM CUSTOMERS WHERE CUSTOMER_ID = " + std::to_string(idToRemove) };
		stmt->executeUpdate(sqlStatement);
		conn->terminateStatement(stmt);
	}
	else
	{
		std::cout << "You can't remove this id, it is present in orders" << std::endl; //TODO ?? maybe orders can has a method that will return ids?
	}

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);
}

void Customers::retrieveData(Connection* conn) const
{
	SqlStatement sqlQuery{ "SELECT CUSTOMER_ID, CUSTOMER_NAME, PHONE_NUMBER FROM CUSTOMERS" };
	displayTable(conn, sqlQuery);
}
