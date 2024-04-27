#include "Table.hpp"

#include <iostream>

void Table::displayTable(Connection* conn, SqlStatement sqlQuery) const
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
