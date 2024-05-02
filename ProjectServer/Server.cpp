#include "Server.h"


Server::Server() : m_database(new DatabaseAccess()), m_handlerFactory(RequestHandlerFactory(m_database))
{
	m_communicator = new Communicator(m_handlerFactory);
}

Server::~Server()
{
	m_database->close();
	m_database = nullptr;

	m_communicator = nullptr;
	m_database = nullptr;
}

void Server::run()
{
	m_communicator->startHandleRequests();
}
