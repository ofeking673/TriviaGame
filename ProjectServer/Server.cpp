#include "Server.h"

// Initialize static members
Server* Server::instance = nullptr;
std::once_flag Server::initInstanceFlag;


Server::Server() :
	m_database(DatabaseAccess::getInstance()),
	m_handlerFactory(RequestHandlerFactory::getInstance(&m_database)),
	m_communicator(&Communicator::getInstance(m_handlerFactory))
{
	std::srand(std::time(0));
}

void Server::initSingleton()
{
	instance = new Server();
}

Server& Server::getInstance()
{
	std::call_once(initInstanceFlag, &Server::initSingleton);
	return *instance;
}

Server::~Server()
{
	m_database.close();
	m_communicator = nullptr;
}

void Server::run()
{
	m_communicator->startHandleRequests();
}
