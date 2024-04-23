#pragma once

#include <occi.h>

using namespace oracle::occi;

class DatabaseConnection
{
private:
	Environment* enviroment{ nullptr };
	Connection* connection{ nullptr };
public:
	DatabaseConnection();
	~DatabaseConnection();
	DatabaseConnection(const DatabaseConnection&) = delete;
	DatabaseConnection(DatabaseConnection&&) = delete;
	DatabaseConnection& operator=(const DatabaseConnection&) = delete;
	DatabaseConnection& operator=(DatabaseConnection&&) = delete;
	Connection* getConnection() const;
};