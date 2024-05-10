#pragma once

#include <vector>
#include <string>

//TODO RAII should be done here but for some reason including xmllite.h and Shlwapi.h here causes random error in Database class in performOperation() method

class XmlWriter
{
public:
	void writeToFile(const std::vector<std::string>&) const;
};