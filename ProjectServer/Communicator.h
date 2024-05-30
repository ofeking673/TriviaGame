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

//offset of how many characters until json starts (1 + 4 bytes)
#define JSON_OFFSET 40
//size of buffer for socket reading
#define READ_SIZE 1000
// accept new clients and handle them.
class Communicator
{
public:
	Communicator(RequestHandlerFactory handlerFactory);
	~Communicator();
	//void serve();
	
	void startHandleRequests();

private:
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