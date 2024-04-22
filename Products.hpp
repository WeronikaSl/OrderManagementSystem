#pragma once
#include "Table.hpp"

class Products : public Table
{
public:
	void addData(Connection*) const override;
	void updateData(Connection*) const override;
	void deleteData(Connection*, Id) const override;
	void retrieveData(Connection*) const override;
};