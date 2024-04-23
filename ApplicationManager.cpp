#include "ApplicationManager.hpp"
#include "Types.hpp"
#include <iostream>

int AppplicationManager::chooseMenuOption() const //TODO is it a good method name?
{
	int menuOption{ 0 };
	std::cout << "What do you want to do?" << std::endl;

	for (std::string operationName : database.getOperationsNames())
	{
		std::cout << operationName << " - choose " << menuOption << std::endl;
		++menuOption;
	}

	return userInterface.getInputNumber();
}

void AppplicationManager::run()
{
	database.performOperation(static_cast<DatabaseOpetation>(chooseMenuOption())); //TODO add loop to be able to choose multiple options
}
