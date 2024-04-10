#pragma once
#include "Types.hpp"
#include "UserInterface.hpp"
#include <array>
#include <vector>
#include <string>
#include <unordered_set>

//TODO implemented with STL containers first, change to real database later

class Database
{
private:
	UserInterface userInterface;
	std::array<std::vector<std::string>, 3> products
		{ std::vector<std::string>{"ProductIdentifier", "1"}, std::vector<std::string>{"ProductName", "White Chocolate"}, std::vector<std::string>{"ProductQuantity", "50"}}; //TODO change to table in database
	
	std::array<std::vector<std::string>, 3> customers
		{ std::vector<std::string>{"CustomerIdentifier", "1"}, std::vector<std::string>{"CustomerName", "Michael Scott"}, std::vector<std::string>{"PhoneNumber", "123456"}}; //TODO change to table in database
	
	std::array<std::vector<std::string>, 3> orders
		{ std::vector<std::string>{"OrderIdentifier", "1"}, std::vector<std::string>{"CustomerId", "1"}, std::vector<std::string>{"ProductId", "1"}}; //TODO change to table in database

	void addData(const std::unordered_set<std::string>&); //TODO check if you dont prevent copy elision here
	void updateData(const std::unordered_set<std::string>&);
	void deleteData(const std::unordered_set<std::string>&);
	void retrieveData(const std::unordered_set<std::string>&);
	void add(std::array<std::vector<std::string>, 3>&, const std::unordered_set<std::string>&); //TODO rename
	void retrieve(std::array<std::vector<std::string>, 3>, const std::unordered_set<std::string>&) const; //TODO rename
	void displayColumns() const;
	std::unordered_set<std::string> chooseColumns() const;
public:
	void performOperation(DatabaseOpetation);
};