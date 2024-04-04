#include "Communicator.h"

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

Communicator::Communicator()
{
	// notice that we step out to the global namespace
// for the resolution of the function socket
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	// create new thread for handling message

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		handleNewClient();
		TRACE("accepting client...");
	}
}

// listen to connecting requests from clients
// accept them, and create thread for each client
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}


void Communicator::handleNewClient()
{
	// Accept client
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
	m_clients[client_socket] = new LoginRequestHandler();


	// Handle client (send or recieve messages)
	char* buf = new char[100];
	std::string sendBuf;

	try
	{
		while (buf[0] != 'x')
		{
			for (int i = 0; i < 100; i++)
			{
				buf[i] = 0;
			}
			recv(client_socket, buf, 100, 0);

			TRACE("%s", buf);

			sendBuf = "Recieved";
			if (strcmp(buf, "Hello") == 0)
			{
				sendBuf = "Hello!";
			}

			send(client_socket, sendBuf.c_str(), sendBuf.size(), 0);
		}
		TRACE("Client sent EXIT and quit.");
	}
	catch (const std::exception& e)
	{
		TRACE("Something went wrong in socket %s, what=%s", m_clients[client_socket], e.what());
	}

	closesocket(client_socket);
}