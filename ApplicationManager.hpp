#pragma once

#include "UserInterface.hpp"
#include "Database.hpp"

class AppplicationManager
{
private:
	UserInterface userInterface;
	Database database;
	int chooseMenuOption() const;
public:
	void run();
};