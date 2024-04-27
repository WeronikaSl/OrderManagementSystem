#include "Orders.hpp"

#include <iostream>

void Orders::addData(Connection* conn) const
{
	std::cout << "Enter value for column 1: ";
	std::string value1{ userInterface.getInputWord() };

	std::cout << "Enter value for column 2: ";
	std::string value2{ userInterface.getInputWord() };

	std::cout << "Enter value for column 3: ";
	std::string value3{ userInterface.getInputWord() };

	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "INSERT INTO ORDERS (ORDER_ID, CUSTOMER_ID, PRODUCT_ID) VALUES(" + value1 + ", " + value2 + ", " + value3 + ")" };
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}

void Orders::updateData(Connection* conn) const
{
	std::cout << "Enter ID that you want to update: ";
	std::string rowId{ userInterface.getInputWord() };

	std::cout << "Enter column name that you want to update: ";
	std::string columnName{ userInterface.getInputWord() };

	std::cout << "Enter value that you want to update it to: ";
	std::string newValue{ userInterface.getInputWord() };

	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "UPDATE ORDERS SET " + columnName + " = '" + newValue + "' WHERE ORDER_ID = " + rowId }; //'' put around integer values done for simplicity, it souldn't be done like this because it forces database to do implicit conversion and it slows down the program which would be significant for larger amounts of data
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}

void Orders::deleteData(Connection* conn, Id idToRemove) const
{
	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "DELETE FROM ORDERS WHERE ORDER_ID = " + std::to_string(idToRemove) };
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}

void Orders::retrieveData(Connection* conn) const
{
	SqlStatement sqlQuery{ "SELECT ORDER_ID, CUSTOMER_ID, PRODUCT_ID FROM ORDERS" };
	displayTable(conn, sqlQuery);
}
