#include "ApplicationManager.hpp"

#include "Types.hpp"

#include <iostream>

int AppplicationManager::chooseMenuOption() const
{
	std::cout << "What do you want to do?" << std::endl;

	for (int i{ 0 }; i < database.getOperationsNames().size(); ++i)
	{
		std::cout << database.getOperationsNames()[i] << " - choose " << i << std::endl;
	}

	return userInterface.getInputNumber();
}

void AppplicationManager::run()
{
	database.performOperation(static_cast<DatabaseOpetationType>(chooseMenuOption()));
}
