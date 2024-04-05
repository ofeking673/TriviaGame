#include "MagshMessageServer.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>

// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

using std::string;
using std::mutex;
using std::unique_lock;
using std::vector;


MagshMessageServer::MagshMessageServer()
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception( __FUNCTION__ " - socket");
}

MagshMessageServer::~MagshMessageServer()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_socket);
	}
	catch (...) {}
}

void MagshMessageServer::serve()
{
	bindAndListen();

	// create new thread for handling message

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		acceptClient();
		TRACE("accepting client...");
	}
}


// listen to connecting requests from clients
// accept them, and create thread for each client
void MagshMessageServer::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void MagshMessageServer::acceptClient()
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	std::thread tr(&MagshMessageServer::clientHandler, this, client_socket);
	tr.detach();
	_users[client_socket] = new LoginRequestHandler();
}



void MagshMessageServer::clientHandler(const SOCKET client_socket)
{
	char buf[6] = {0};
	const char* sendBuf = "Hello!";
	try
	{
		for (int i = 0; i < 5; i++)
		{

			recv(client_socket, buf, 5, 0);
			TRACE("%s", buf);

			send(client_socket, sendBuf, strlen(sendBuf), 0);
		}
	}
	catch (const std::exception& e)
	{
		TRACE("Something went wrong in socket %s, what=%s", _users[client_socket], e.what());
	}

	closesocket(client_socket);
}
