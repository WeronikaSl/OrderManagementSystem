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
	SqlStatement sqlStatement{ "INSERT INTO CUSTOMERS (CUSTOMER_ID, CUSTOMER_NAME, PHONE_NUMBER) VALUES(" + value1 + ", '" + value2 + "', " + value3 + ")" };
	stmt->executeUpdate(sqlStatement);
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
	SqlStatement sqlStatement{ "UPDATE CUSTOMERS SET " + columnName + " = '" + newValue + "' WHERE CUSTOMER_ID = " + rowId }; //'' put around integer values done for simplicity, it souldn't be done like this because it forces database to do implicit conversion and it slows down the program which would be significant for larger amounts of data
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}

void Customers::deleteData(Connection* conn, Id idToRemove) const
{
	Statement* stmt = conn->createStatement("SELECT CUSTOMER_ID FROM ORDERS");
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
		std::cout << "You can't remove this id" << std::endl;
	}

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);
}

void Customers::retrieveData(Connection* conn) const
{
	SqlStatement sqlQuery{ "SELECT CUSTOMER_ID, CUSTOMER_NAME, PHONE_NUMBER FROM CUSTOMERS" };

	Statement* stmt = conn->createStatement();
	stmt->setSQL(sqlQuery);
	ResultSet* rs = stmt->executeQuery();

	std::cout << std::endl;

	std::string elem1{};
	std::string elem2{};
	std::string elem3{};
	
	std::vector<std::string> elems{"CUSTOMERS"};

	while (rs->next())
	{
		elem1 = rs->getString(1);
		elem2 = rs->getString(2);
		elem3 = rs->getString(3);

		elems.push_back("CUSTOMER_ID");
		elems.push_back(elem1);
		elems.push_back("CUSTOMER_NAME");
		elems.push_back(elem2);
		elems.push_back("PHONE_NUMBER");
		elems.push_back(elem3);

		std::cout << elem1 << " " << elem2 << " " << elem3 << std::endl;
	}

	std::cout << std::endl;

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);

	std::cout << "Do you want to write data to xml file? 1 - yes, 0 - no: ";
	int userInput{ userInterface.getInputNumber() };

	if (userInput == 1)
	{
		xmlWriter.writeToFile(elems);
	}
}
