#include "MenuRequestHandler.h"

// Check if request is relevant to menu request handler
bool MenuRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
    return (requestInfo.id == CreateRoom || requestInfo.id == GetRooms ||
            requestInfo.id == GetPlayersInRoom || requestInfo.id == JoinRoom ||
            requestInfo.id == GetPersonalStats || requestInfo.id == GetHighScores ||
			requestInfo.id == Logout);
}

RequestResult MenuRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Check if request relevant
	if (isRequestRelevant(requestInfo))
	{

		if (requestInfo.id == CreateRoom)
		{
			// CreateRoom
			requestResult = createRoom(requestInfo);
		}
		else if (requestInfo.id == GetRooms)
		{
			// GetRooms
			requestResult = getRooms(requestInfo);
		}
		else if (requestInfo.id == GetPlayersInRoom)
		{
			// GetPlayersInRoom
			requestResult = getPlayersInRoom(requestInfo);
		}
		else if (requestInfo.id == JoinRoom)
		{
			// JoinRoom
			requestResult = joinRoom(requestInfo);
		}
		else if (requestInfo.id == GetPersonalStats)
		{
			// Get personal statistics
			requestResult = getPersonalStats(requestInfo);
		}
		else if (requestInfo.id == GetHighScores)
		{
			// Get high score list
			requestResult = getHighScore(requestInfo);
		}
		else if (requestInfo.id == Logout)
		{
			// Logout
			requestResult = signout(requestInfo);
		}
		else
		{
			// Error
			requestResult = error(requestInfo);
		}

	}
	else
	{
		// Error
		requestResult = error(requestInfo);
	}

	return requestResult;
}

/// <summary>
/// Logout a user from the system
/// Gets Request info, parse its' data. 
/// Sends the data to loginMannager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::signout(Requestinfo requestInfo)
{
	RequestResult requestResult;
	LogoutResponse logoutResponse;

	// Logout the user through login manager who uses the Database
	if(m_handlerFactory.getLoginManager().logout(m_user.getUsername()))
	{	// Succeful Logout

		// TO-DO think about handler after logout. should be nullptr or something else?
		requestResult.newHandler = nullptr;

		// Succeful Logout status
		logoutResponse.status = TEMP_LOGOUT_RESPONSE_STATUS;

	}
	else
	{	//Failed to Logout

		// Stay in menu request handler
		MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
		requestResult.newHandler = menuRequestHandler;

		// Failed Logout status
		logoutResponse.status = TEMP_FAIL_LOGOUT_RESPONSE_STATUS;
	}

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(logoutResponse);

	return requestResult;
}

/// <summary>
/// Get a vector of all the rooms.
/// Gets Request info, parse its' data. 
/// Sends the data to RoomManager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::getRooms(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Get all rooms through room manager
	std::vector<RoomData> rooms = m_handlerFactory.getRoomManager().getRooms();

	// Stay in menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;

	// Create response
	GetRoomsResponse getRoomsResponse;
	getRoomsResponse.status = TEMP_GET_ROOMS_RESPONSE_STATUS;
	getRoomsResponse.rooms = rooms;

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);

	return requestResult;
}

/// <summary>
/// Get a vector of all players in a specific room.
/// Gets Request info, parse its' data. 
/// Sends the data to RoomManager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::getPlayersInRoom(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Deserialize request
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buf);

	// Get all the players in a desired room through room manager
	std::vector<std::string> players = m_handlerFactory.getRoomManager().getRoom(getPlayersInRoomRequest.roomId).getAllUsers();
	
	// Stay in menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;

	// Create response
	GetPlayersInRoomResponse getPlayersInRoomResponse;
	getPlayersInRoomResponse.status = TEMP_GET_PLAYERS_IN_ROOM_RESPONSE_STATUS;
	getPlayersInRoomResponse.players = players;


	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);

	return requestResult;
}

/// <summary>
/// Gets all the statistics of current user
/// Gets Request info, parse its' data. 
/// Sends the data to statisticsManager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::getPersonalStats(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Get the statistics of user
	std::vector<std::string> personalStats = m_handlerFactory.getStatisticsManager().getUserStatistics(m_user.getUsername());

	// Stay in menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;

	// Create response
	GetPersonalStatsResponse getPersonalStatsResponse;
	getPersonalStatsResponse.statistics = personalStats;
	getPersonalStatsResponse.status = TEMP_GET_PERSONAL_STATS_RESPONSE_STATUS;

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse);

	return requestResult;
}

/// <summary>
/// Gets the high score
/// Gets Request info, parse its' data. 
/// Sends the data to statisticsManager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::getHighScore(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Get the high score
	std::vector<std::string> highScore = m_handlerFactory.getStatisticsManager().getHighScore();

	// Stay in menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;

	// Create response
	GetHighScoreResponse getHighScoreResponse;
	getHighScoreResponse.statistics = highScore;
	getHighScoreResponse.status = TEMP_GET_HIGH_SCORE_RESPONSE_STATUS;

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse);

	return requestResult;
}

/// <summary>
/// Join a user to a specific room
/// Gets Request info, parse its' data. 
/// Sends the data to RoomManager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::joinRoom(Requestinfo requestInfo)
{
	RequestResult requestResult;
	JoinRoomResponse joinRoomResponse;

	// Deserialize request
	std::vector<RoomData> rooms = m_handlerFactory.getRoomManager().getRooms();
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buf);

	// Stay in menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;

	// Add the user to the desired room
	if (m_handlerFactory.getRoomManager().getRoom(joinRoomRequest.roomId).addUser(m_user))
	{
		joinRoomResponse.status = TEMP_JOIN_ROOM_RESPONSE_STATUS;
	}
	else
	{
		joinRoomResponse.status = TEMP_FAIL_JOIN_ROOM_RESPONSE_STATUS;
	}

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse);

	return requestResult;
}

/// <summary>
/// Creates a new room based on given information
/// Gets Request info, parse its' data. 
/// Sends the data to RoomManager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult MenuRequestHandler::createRoom(Requestinfo requestInfo)
{
	RequestResult requestResult;
	CreateRoomResponse createRoomResponse;
	// Deserialize request
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buf);

	// Parse all the gotten room data into a RoomData variable to send when creating the room
	RoomData roomData;
	roomData.id = 0; // Will generate a unique id in function
	roomData.isActive = false; // Room starts as not active (waiting to start the game)
	roomData.maxPlayers = createRoomRequest.maxUsers;
	roomData.name = createRoomRequest.roomName;
	roomData.numOfQuestionsInGame = createRoomRequest.questionsCount;
	roomData.timePerQuestion = createRoomRequest.answerTimeout;

	// Stay in menu request handler
	// TO-DO may need to change handler...
	std::cout << "Trying to new handler\n";
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;
	std::cout << "Trying to create room\n";
	//create room manager
	std::cout << "Trying to room manager create room\n";
	auto roomManager = m_handlerFactory.getRoomManager();

	if (roomManager.createRoom(m_user, roomData))
	{
		createRoomResponse.status = TEMP_CREATE_ROOM_RESPONSE_STATUS;
	}
	else
	{
		createRoomResponse.status = TEMP_FAIL_CREATE_ROOM_RESPONSE_STATUS;
	}

	std::cout << "Trying to serialize\n";
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(createRoomResponse);
	std::cout << "Trying to return\n";
	return requestResult;
}

// In case of error - Call the function to return response indicates there was an error
RequestResult MenuRequestHandler::error(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	ErrorResponse errorResponse;
	errorResponse.message = "Error in Menu Request Handler.";
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

	// New handler is nullptr - indicates Error
	requestResult.newHandler = nullptr;
	return requestResult;
}
