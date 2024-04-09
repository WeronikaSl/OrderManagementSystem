#pragma once
#include "Types.hpp"

//TODO implemented with STL containers first, change to real database later

class Database
{
private:
	void addData();
	void updateData();
	void deleteData();
	void retrieveData();
public:
	void performOperation(DatabaseOpetation);
};