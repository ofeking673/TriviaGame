#include "Server.h"


Server::Server()
{
	m_database = new DatabaseAccess();
	m_handlerFactory = new RequestHandlerFactory(m_database);
	m_communicator = new Communicator(*m_handlerFactory);
}

void Server::run()
{
	m_communicator->startHandleRequests();
}
