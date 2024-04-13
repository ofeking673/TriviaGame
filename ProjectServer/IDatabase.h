#pragma once
#include <string>

class IDatabase
{
public:
	virtual ~IDatabase() {};

	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(std::string) = 0;
	virtual int doesPasswordMatch(std::string, std::string) = 0;
	virtual int addNewUser(std::string, std::string, std::string) = 0;
};