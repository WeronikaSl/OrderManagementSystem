#pragma once

#include <string>

//this class shouln't know what input will be used for

class UserInterface
{
public:
	int getInputNumber() const;
	std::string getInputWord() const;
};