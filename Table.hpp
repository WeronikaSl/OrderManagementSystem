#pragma once

#include "Types.hpp"
#include "UserInterface.hpp"

#include <occi.h>

using namespace oracle::occi;

class Table
{
protected:
	UserInterface userInterface;

	void displayTable(Connection*, SqlStatement) const;
public:
	virtual void addData(Connection*) const = 0;
	virtual void updateData(Connection*) const = 0;
	virtual void deleteData(Connection*, Id) const = 0;
	virtual void retrieveData(Connection*) const = 0;
};