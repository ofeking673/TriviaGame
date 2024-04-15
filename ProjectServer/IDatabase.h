#pragma once
#include <string>
#include <map>
class IDatabase
{
public:
	virtual ~IDatabase() {};

	virtual void open(std::string fileName) = 0;
	virtual void close() = 0;

	virtual void InitDb() = 0;

	virtual bool doesUserExist(std::string name) = 0;
	virtual void addUser(std::string name, std::string pass, std::string email) = 0;
	virtual bool isPassCorrect(std::string name, std::string pass) = 0;
	virtual std::map<std::string, std::string> getAccountData(std::string name) = 0;
};