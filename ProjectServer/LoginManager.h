#pragma once
#include "LoggedUser.h"
#include "DatabaseAccess.h"
#include <vector>

class LoginManager
{
public:
	LoginManager(std::string fileName);
	~LoginManager();
	bool login(std::string name, std::string pass);
	bool signup(std::string name, std::string pass, std::string email);

	bool logOut(std::string name);

private:
	std::vector<LoggedUser*> m_loggedUsers;
	DatabaseAccess db;
};

