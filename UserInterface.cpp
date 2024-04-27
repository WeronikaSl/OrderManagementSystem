#include "UserInterface.hpp"

#include <iostream>

int UserInterface::getInputNumber() const
{
	int input{ 0 };
	std::cin >> input;
    return input;
}

std::string UserInterface::getInputWord() const
{
	std::string input{};
	std::cin >> input;
	return input;
}
