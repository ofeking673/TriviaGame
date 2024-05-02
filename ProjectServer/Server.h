#pragma once
#include "Communicator.h"
#include "sqlite3.h"
class Server
{
public:
	Server();
	~Server();

	void run();
private:
	Communicator* m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};