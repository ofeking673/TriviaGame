#pragma once
#include <iostream>
#include "sqlite3.h"
#include "IDatabase.h"
#include <io.h>

class DatabaseAccess : public IDatabase
{
	DatabaseAccess(std::string fileName) 
	{
		int test = _access(fileName.c_str(), 0);
		sqlite3_open(fileName.c_str(), &db);
		
		if (test == -1)
		{
			InitDb();
		}
	};

	~DatabaseAccess() { sqlite3_close(db); db = nullptr; };

	virtual void InitDb() override;
	
	virtual bool doesUserExist(std::string name) override;
	virtual void addUser(std::string name, std::string pass, std::string email) override;
	virtual bool isPassCorrect(std::string name, std::string pass) override;
private:
	sqlite3* db;
};

