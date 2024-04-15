#pragma once
#include <iostream>
#include "sqlite3.h"
#include "IDatabase.h"
#include <io.h>

class DatabaseAccess : public IDatabase
{
public:
	DatabaseAccess() 
	{
		open(FILENAME);
	};

	virtual void open(std::string fileName) override
	{
		int test = _access(fileName.c_str(), 0);
		sqlite3_open(fileName.c_str(), &db);

		if (test == -1)
		{
			InitDb();
		}
	};

	virtual void close() override {
		sqlite3_close(db);
		db = nullptr;
	};


	~DatabaseAccess() { close(); };

	virtual void InitDb() override;
	
	virtual bool doesUserExist(std::string name) override;
	virtual void addUser(std::string name, std::string pass, std::string email) override;
	virtual bool isPassCorrect(std::string name, std::string pass) override;

	virtual std::map<std::string, std::string> getAccountData(std::string name) override;

	static int check(void* data, int argc, char** argv, char** azColName);
	static int checkPass(void* data, int argc, char** argv, char** azColName);
	static int getData(void* data, int argc, char** argv, char** azColName);

private:
	sqlite3* db;
};

