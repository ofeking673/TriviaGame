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

Communicator::Communicator(RequestHandlerFactory handlerFactory):m_handlerFactory(handlerFactory)
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
		acceptClient();
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


void Communicator::handleNewClient(const SOCKET client_socket)
{
	char* buf = new char[READ_SIZE];
	std::string sendBuf;
	
	try
	{
		while (true)
		{
			for (int i = 0; i < READ_SIZE; i++)
			{
				buf[i] = 0;
			}

			recv(client_socket, buf, READ_SIZE, 0);
			std::string str(buf);
			Buffer deserialize;
			
			std::string decodedstr = JsonRequestPacketDeserializer::binaryDecoder(str);
			std::string jsonStr = decodedstr.substr(5);

			Requestinfo info; 
			breakDownStr(info, decodedstr);

			std::cout << "'" << info.id << "'";
			switch (info.id) //TODO: add more types
			{
			case SignUp:
			case Login:
			{
				LoginRequestHandler* login = new LoginRequestHandler(m_handlerFactory);
				m_clients[client_socket] = login;

				RequestResult result = login->HandleRequest(info);
				
				sendBuf = std::string(result.response.data.begin(), result.response.data.end());
				send(client_socket, sendBuf.c_str(), sendBuf.length(), 0);
				break;
			}
			default:
				throw std::runtime_error("Invalid request id :"+ std::to_string(info.id) + "\n");
			}
		}
		TRACE("Client sent EXIT and quit.");
	}
	catch (const std::exception& e)
	{
		TRACE("Something went wrong in socket %s, what=%s", m_clients[client_socket], e.what());
	}

	closesocket(client_socket);
}

void Communicator::breakDownStr(Requestinfo& info, std::string buf)
{
	Buffer buffer;
	
	std::string jsonStr = buf.substr(5);
	for (int i = 0; i < jsonStr.size(); i++)
	{
		buffer.data.push_back(jsonStr[i]);
	}

	info.buf = buffer;
	info.id = getIdFromStr(buf);

	info.time = clock();
}

RequestId Communicator::getIdFromStr(std::string str)
{
	switch (str[0])
	{
	case '0':
		return Login;
	case '1':
		return SignUp;
	default:
		break;
	}
}

void Communicator::acceptClient()
{
	// Accept client
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
	m_clients[client_socket] = m_handlerFactory.createLoginRequestHandler();
}

void Communicator::sendResponse(Requestinfo* request)
{
	//we analyze each request class
	Buffer buf;
	switch (request->id)
	{
		case Login:
		{
			LoginResponse login;
			login.status = request->id;
			buf = m_serializer.serializeResponse(login);
			break;
		}
		case SignUp:
		{
			SignupResponse signup;
			signup.status = request->id;
			buf = m_serializer.serializeResponse(signup);
			break;
		}
	}

}
