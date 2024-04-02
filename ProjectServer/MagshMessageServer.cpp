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
//
//// remove the user from queue
//void MagshMessageServer::safeDeleteUser(const SOCKET id)
//{
//	try
//	{
//		for (unsigned int i = 0; i < _clients.size(); i++)
//		{
//			if (_clients[i].first == id)
//			{
//				TRACE("REMOVED %d, %s from clients list", id, _clients[i].second.c_str());
//				_clients.erase(_clients.begin() + i);
//				
//			}
//		}
//	}
//	catch (...) {}
//	
//}
//
//void MagshMessageServer::handleReceivedMessages()
//{
//	int msgCode = 0;
//	SOCKET clientSock = 0;
//	string userName;
//	while (true)
//	{
//		
//	}
//}
//
//
//std::string MagshMessageServer::getAllUsernames()
//{
//	const std::string delimiter = "&";
//	return std::accumulate(std::begin(_clients), std::end(_clients), std::string(),
//		[delimiter](const string& lhs, const std::pair<SOCKET, string>& rhs)
//		{
//			if (lhs.empty()) return rhs.second;
//			else
//				return lhs + delimiter + rhs.second; });
//}
//
//
//// get current user name (the writer)
//std::string MagshMessageServer::getCurrentUser()
//{
//
//	if (_clients.size() < 1)
//		return "";
//
//	return _clients[0].second;
//}
//
//// get next user in queue
//std::string MagshMessageServer::getNextUser()
//{
//	if (_clients.size() < 2)
//		return "";
//
//	return _clients[1].second;
//}
//
//std::string MagshMessageServer::get_user_name(const SOCKET id)
//{
//	for (const std::pair<SOCKET, string>& elem : _clients)
//	{
//		if (elem.first == id)
//		{
//			return elem.second;
//		}		
//	}
//	return {};
//}
