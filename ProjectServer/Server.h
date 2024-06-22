#pragma once
#include "Communicator.h"
#include "sqlite3.h"
class Server
{
public:
	// Access the single instance
	static Server& getInstance();

	// Delete copy constructor and assignment operator
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;

	~Server();

	void run();
private:

	// Private ctor
	Server();

	// Static method to initialize the singleton instance
	static void initSingleton();

	// Pointer to the single instance
	static Server* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;


	Communicator* m_communicator;
	DatabaseAccess& m_database;
	RequestHandlerFactory& m_handlerFactory;
};