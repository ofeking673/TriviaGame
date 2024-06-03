#pragma once
#include "DatabaseAccess.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:
	// Public method to access the single instance
	static LoginManager& getInstance();

	// Delete copy constructor and assignment operator
	LoginManager(const LoginManager&) = delete;
	LoginManager& operator=(const LoginManager&) = delete;

	~LoginManager();

	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	bool logout(std::string username);

private:
	// Private ctor
	LoginManager(IDatabase* database);

	// Static method to initialize the singleton instance
	static void initSingleton();

	// Pointer to the single instance
	static LoginManager* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;

	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};