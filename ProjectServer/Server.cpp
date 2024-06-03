#include "Server.h"


Server::Server()
{
	m_database = DatabaseAccess::getInstance();
	m_handlerFactory = new RequestHandlerFactory(m_database);
	m_communicator = new Communicator(*m_handlerFactory);
}

Server::~Server()
{
	m_database->close();
	m_communicator = nullptr;
}

void Server::run()
{
	m_communicator->startHandleRequests();
}
