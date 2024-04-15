#include "Server.h"


Server::Server()
{
	m_database = new DatabaseAccess();
	m_handlerFactory = RequestHandlerFactory(m_database);
}

void Server::run()
{
	m_communicator.startHandleRequests();
}
