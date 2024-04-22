#pragma once
#include "Table.hpp"

class Customers : public Table
{
public:
	void addData(Connection*) const override;
	void updateData(Connection*) const override;
	void deleteData(Connection*, Id) const override;
	void retrieveData(Connection*) const override;

};