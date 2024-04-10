#pragma once
#include <string>

class UserInterface
{
public:
	int getInputNumber() const; //TODO this class shouln't know what input will be used for 
	std::string getInputWord() const;
};