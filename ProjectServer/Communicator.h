#pragma once

#include <deque>
#include <map>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "Helper.h"
#include "LoginRequestHandler.h"

// Q: why do we need this class ?
// A: this is the main class which holds all the resources,
// accept new clients and handle them.
class Communicator
{
public:
	Communicator();
	~Communicator();
	//void serve();
	
	// I really don't know if this is what they
	// meant to do in this function
	void startHandleRequests();

private:
	void bindAndListen();

	// Ofek, the function 'acceptClient()' was not in the UML but I think
	// it meant to be here toogether with 'clientHandler()'
	// If you think of a betteer way please feel free to change
	void handleNewClient();



	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	//void acceptClient();
	//void clientHandler(const SOCKET client_socket);
	//void handleReceivedMessages();
	/*void safeDeleteUser(const SOCKET id);


	std::string getCurrentUser();
	std::string getNextUser();
	std::string get_user_name(const SOCKET id);
	std::string getAllUsernames();*/


};