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
class MagshMessageServer
{
public:
	MagshMessageServer();
	~MagshMessageServer();
	void serve();


private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(const SOCKET client_socket);
	void handleReceivedMessages();
		
	SOCKET _socket;
	std::map<SOCKET, LoginRequestHandler*> _users;
};

