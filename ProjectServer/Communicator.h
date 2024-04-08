#pragma once

#include <deque>
#include <map>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"


// accept new clients and handle them.
class Communicator
{
public:
	Communicator();
	~Communicator();
	//void serve();
	
	void startHandleRequests();

private:
	void bindAndListen();

	void handleNewClient(const SOCKET client_socket);


	JsonResponsePacketSerializer m_serializer;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	// More functions
	void acceptClient();
	void sendResponse(packetType type, IRequestHandler* request);
	



	//void clientHandler(const SOCKET client_socket);
	//void handleReceivedMessages();
	/*void safeDeleteUser(const SOCKET id);


	std::string getCurrentUser();
	std::string getNextUser();
	std::string get_user_name(const SOCKET id);
	std::string getAllUsernames();*/


};