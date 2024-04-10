#include "ApplicationManager.hpp"
#include "Types.hpp"
#include <iostream>

int AppplicationManager::chooseMenuOption() const //TODO is it a good method name?
{
	std::cout << "What do you want to do?" << std::endl
		<< "Add data - choose 0" << std::endl
		<< "Update data - choose 1" << std::endl
		<< "Delete data - choose 2" << std::endl
		<< "Retrieve data - choose 3" << std::endl;
	return userInterface.getInputNumber();
}

void AppplicationManager::run()
{
	database.performOperation(static_cast<DatabaseOpetation>(chooseMenuOption()));
}
