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
#include "RequestHandlerFactory.h"


//size of buffer for socket reading
#define READ_SIZE 1000
// accept new clients and handle them.
class Communicator
{
public:
	// Access the single instance
	static Communicator& getInstance(RequestHandlerFactory& handlerFactory);

	// Delete copy constructors
	Communicator(const Communicator&) = delete;
	Communicator& operator=(const Communicator&) = delete;


	~Communicator();
	//void serve();
	
	void startHandleRequests();

private:
	// Private ctor
	Communicator(RequestHandlerFactory& handlerFactory);

	// Static method to initialize the singleton instance
	static void initSingleton(RequestHandlerFactory& handlerFactory);

	// Pointer to the single instance
	static Communicator* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;





	void bindAndListen();
	void handleNewClient(const SOCKET client_socket);
	void breakDownStr(Requestinfo& info, std::string buf);
	RequestId getIdFromStr(std::string str);

	JsonResponsePacketSerializer m_serializer;
	SOCKET m_serverSocket;
	std::map<SOCKET, std::pair<IRequestHandler*, LoggedUser>> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	// More functions
	void acceptClient();
};