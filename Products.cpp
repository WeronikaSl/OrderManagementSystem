#include "Products.hpp"

#include "Types.hpp"

#include <iostream>
#include <unordered_set>

void Products::addData(Connection* conn) const
{
	std::cout << "Enter value for column 1: ";
	std::string value1{ userInterface.getInputWord() };

	std::cout << "Enter value for column 2: ";
	std::string value2{ userInterface.getInputWord() };

	std::cout << "Enter value for column 3: ";
	std::string value3{ userInterface.getInputWord() };

	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "INSERT INTO PRODUCTS (PRODUCT_ID, PRODUCT_NAME, PRICE_PER_UNIT) VALUES(" + value1 + ", '" + value2 + "', " + value3 + ")" };
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}

void Products::updateData(Connection* conn) const
{
	std::cout << "Enter ID that you want to update: ";
	std::string rowId{ userInterface.getInputWord() };

	std::cout << "Enter column name that you want to update: ";
	std::string columnName{ userInterface.getInputWord() };

	std::cout << "Enter value that you want to update it to: ";
	std::string newValue{ userInterface.getInputWord() };

	Statement* stmt = conn->createStatement();
	SqlStatement sqlStatement{ "UPDATE PRODUCTS SET " + columnName + " = '" + newValue + "' WHERE PRODUCT_ID = " + rowId }; //'' put around integer values done for simplicity, it souldn't be done like this because it forces database to do implicit conversion and it slows down the program which would be significant for larger amounts of data
	stmt->executeUpdate(sqlStatement);
	conn->terminateStatement(stmt);
}

void Products::deleteData(Connection* conn, Id idToRemove) const
{
	Statement* stmt = conn->createStatement("SELECT PRODUCT_ID FROM ORDERS");
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
		SqlStatement sqlStatement{ "DELETE FROM PRODUCTS WHERE PRODUCT_ID = " + std::to_string(idToRemove) };
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

void Products::retrieveData(Connection* conn) const
{
	SqlStatement sqlQuery{ "SELECT PRODUCT_ID, PRODUCT_NAME, PRICE_PER_UNIT FROM PRODUCTS" };
	Statement* stmt = conn->createStatement();
	stmt->setSQL(sqlQuery);
	ResultSet* rs = stmt->executeQuery();

	std::cout << std::endl;

	std::string retrievedData1{};
	std::string retrievedData2{};
	std::string retrievedData3{};

	std::vector<std::string> dataForXml{ "PRODUCTS" };

	while (rs->next())
	{
		retrievedData1 = rs->getString(1);
		retrievedData2 = rs->getString(2);
		retrievedData3 = rs->getString(3);

		dataForXml.push_back("PRODUCT_ID");
		dataForXml.push_back(retrievedData1);
		dataForXml.push_back("PRODUCT_NAME");
		dataForXml.push_back(retrievedData2);
		dataForXml.push_back("PRICE_PER_UNIT");
		dataForXml.push_back(retrievedData3);

		std::cout << retrievedData1 << " " << retrievedData2 << " " << retrievedData3 << std::endl;
	}

	std::cout << std::endl;

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);

	std::cout << "Do you want to write data to xml file? 1 - yes, 0 - no: ";
	int userInput{ userInterface.getInputNumber() };

	if (userInput == 1)
	{
		xmlWriter.writeToFile(dataForXml);
	}
}
