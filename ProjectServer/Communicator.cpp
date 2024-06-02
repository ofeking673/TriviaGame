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

mutex mtx;

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
			
			Requestinfo info; 
			breakDownStr(info, decodedstr);

			std::cout << "'" << info.id << "'";
			mtx.lock();
			RequestResult result = m_clients[client_socket].first->HandleRequest(info);
			mtx.unlock();
			// Set current handler as new handler came back from handler request
			m_clients[client_socket].first = result.newHandler;
			if (m_clients[client_socket].second.getUsername() == "")
			{
				m_clients[client_socket].second = result.newHandler->getUser();
			}

			sendBuf = std::string(result.response.data.begin(), result.response.data.end());
			send(client_socket, sendBuf.c_str(), sendBuf.length(), 0);

			if (info.id == Logout)
			{
				break;
			}
		}
		TRACE("Client sent EXIT and quit.");
	}
	catch (const std::exception& e)
	{
		TRACE("Something went wrong in socket %s, what=%s", m_clients[client_socket], e.what());

		try
		{
			int gameId = m_handlerFactory.getGameManager().getGameForUser(m_clients[client_socket].second).getGameId();
			if (m_handlerFactory.getGameManager().getGameForUser(m_clients[client_socket].second).removePlayer(m_clients[client_socket].second))
			{
				m_handlerFactory.getGameManager().deleteGame(gameId);
			}

			Room room = m_handlerFactory.getRoomManager().getRoomForUser(m_clients[client_socket].second);
			int id = room.getRoomData().id;

			if (m_handlerFactory.getRoomManager().getRoom(id).removeUser(m_clients[client_socket].second))
			{
				m_handlerFactory.getRoomManager().deleteRoom(id);
			}	

		}
		catch (const std::runtime_error& e)
		{
			goto logout;
		}

		


		logout:
		Requestinfo req;
		req.id = Logout;
		// TO-DO maybe switch to menu request handler. Because only there is the logout.
		// Otherwise it will be only: isRequestRelavant -> false
		m_clients[client_socket].first = (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_clients[client_socket].second);
		m_clients[client_socket].first->HandleRequest(req);
		std::cout << "user Logged out!\n";
	}

	closesocket(client_socket);
}

void Communicator::breakDownStr(Requestinfo& info, std::string buf)
{
	Buffer buffer;

	if (buf.find_first_of("{") != std::string::npos)
	{//{"data":"data"}
		std::string jsonStr = buf.substr(buf.find_first_of("{"));
		for (int i = 0; i < jsonStr.size(); i++)
		{
			buffer.data.push_back(jsonStr[i]);
		}
	}
	
	info.buf = buffer;
	info.id = getIdFromStr(buf);

	info.time = clock();
}

RequestId Communicator::getIdFromStr(std::string str)
{
	switch (std::stoi(str.substr(0, str.find_first_of("|"))))
	{
	case 0:
		return Login;
	case 1:
		return SignUp;
	case 2:
		return CreateRoom;
	case 3:
		return GetRooms;
	case 4:
		return GetPlayersInRoom;
	case 5:
		return JoinRoom;
	case 6:
		return GetPersonalStats;
	case 7:
		return GetHighScores;
	case 8:
		return Logout;
	case 9:
		return CloseRoom;
	case 10:
		return StartGame;
	case 11:
		return GetRoomState;
	case 12:
		return LeaveRoom;
	case 13:
		return Update;
	case 14:
		return LeaveGame;
	case 15:
		return GetQuestion;
	case 16:
		return SubmitAnswer;
	case 17:
		return GetGameResult;
	default:
		return Error69; //we love when this happens

	/* 
	LeaveGame,
	GetQuestion,
	SubmitAnswer,
	GetGameResult,
	*/
		
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
	m_clients[client_socket] = std::make_pair<IRequestHandler*, LoggedUser>((IRequestHandler*)m_handlerFactory.createLoginRequestHandler(), LoggedUser(""));
}
