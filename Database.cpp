#include "Database.hpp"
#include <iostream>
#include <occi.h>

using namespace oracle::occi;

void Database::addData() //TODO implement validating user imput
{
	std::cout << "Data added" << std::endl; //TODO implement logic 
}

void Database::updateData() //TODO implement validating user imput
{
	std::cout << "Data updated" << std::endl; //TODO implement logic 
}

void Database::deleteData() //TODO implement validating user imput
{
	std::cout << "Data removed" << std::endl; //TODO implement logic 
}

void Database::retrieveData(const std::unordered_set<std::string>& chosenColumns) //TODO implement exception handling
{
	Environment* env = Environment::createEnvironment();

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456";
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	Connection* conn = env->createConnection(user, pass, constr);

	Statement* stmt = conn->createStatement();

	stmt->setSQL("SELECT PRODUCT_ID, PRODUCT_NAME, PRICE_PER_UNIT FROM PRODUCTS");

	ResultSet* rs = stmt->executeQuery();

	std::cout << std::endl;

	while (rs->next()) //TODO FIX code copied
	{
		std::string PRODUCT_ID = rs->getString(1);
		std::string PRODUCT_NAME = rs->getString(2);
		int PRICE_PER_UNIT = rs->getInt(3);

		std::cout << PRODUCT_ID << " " << PRODUCT_NAME << " " << PRICE_PER_UNIT << std::endl;
	}

	std::cout << std::endl;

	stmt->setSQL("SELECT CUSTOMER_ID, CUSTOMER_NAME, PHONE_NUMBER FROM CUSTOMERS");

	rs = stmt->executeQuery();

	while (rs->next()) //TODO FIX code copied
	{
		std::string CUSTOMER_ID = rs->getString(1);
		std::string CUSTOMER_NAME = rs->getString(2);
		int PHONE_NUMBER = rs->getInt(3);

		std::cout << CUSTOMER_ID << " " << CUSTOMER_NAME << " " << PHONE_NUMBER << std::endl;
	}

	std::cout << std::endl;

	stmt->setSQL("SELECT ORDER_ID, CUSTOMER_ID, PRODUCT_ID FROM ORDERS");

	rs = stmt->executeQuery();

	while (rs->next()) //TODO FIX code copied
	{
		int ORDER_ID = rs->getInt(1);
		int CUSTOMER_ID = rs->getInt(2);
		int PRODUCT_ID = rs->getInt(3);

		std::cout << ORDER_ID << " " << CUSTOMER_ID << " " << PRODUCT_ID << std::endl;
	}

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);
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
		addData();
		break;
	case DatabaseOpetation::UPDATE:
		updateData();
		break;
	case DatabaseOpetation::DELETE:
		deleteData();
		break;
	case DatabaseOpetation::RETRIEVE:
		retrieveData(chooseColumns());
		break;
	default:
		std::cout << "nothing" << std::endl; //TODO implement logic 
	}
}