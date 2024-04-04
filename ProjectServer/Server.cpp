#include "Server.h"

void Server::run()
{
	// HELP: maybe make a different thread for it?
	// HELP: is this what they want in the function?
	m_communicator.startHandleRequests();
}
