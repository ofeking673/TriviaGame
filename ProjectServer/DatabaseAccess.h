#pragma once
#include <iostream>
#include "sqlite3.h"
#include <io.h>

class DatabaseAccess
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

	void InitDb();
	
	bool doesUserExist(std::string name);
	void addUser(std::string name, std::string pass, std::string email);
	bool isPassCorrect(std::string name, std::string pass);
private:
	sqlite3* db;
};

