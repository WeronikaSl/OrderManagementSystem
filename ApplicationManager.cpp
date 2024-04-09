#include "ApplicationManager.hpp"
#include "Types.hpp"
#include <iostream>

int AppplicationManager::chooseMenuOption() const
{
	std::cout << "What do you want to do?" << std::endl
		<< "Add data - choose 1" << std::endl
		<< "Update data - choose 2" << std::endl
		<< "Delete data - choose 3" << std::endl
		<< "Retrieve data - choose 4" << std::endl;
	return userInterface.getInputNumber();
}

void AppplicationManager::run()
{
	database.performOperation(static_cast<DatabaseOpetation>(chooseMenuOption()));
}
