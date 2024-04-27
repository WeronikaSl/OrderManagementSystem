#include "DatabaseConnection.hpp"

DatabaseConnection::DatabaseConnection() //RAII
{
	enviroment = Environment::createEnvironment();

	std::string user = "OrderManagementSystem "; //local user for pluggable database XEPDB1
	std::string pass = "123456"; //ofc super secure password XD
	std::string constr = "localhost:1521/XEPDB1"; //default pluggable database from Oracle Database Express Edition (XE)

	connection = enviroment->createConnection(user, pass, constr);
}

DatabaseConnection::~DatabaseConnection() //RAII
{
	enviroment->terminateConnection(connection);
	Environment::terminateEnvironment(enviroment);
}

Connection* DatabaseConnection::getConnection() const
{
    return connection;
}
