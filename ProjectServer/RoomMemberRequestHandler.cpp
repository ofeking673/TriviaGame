#include "RoomMemberRequestHandler.h"

// Checks if request relevant for handler
bool RoomMemberRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
	return (requestInfo.id == LeaveRoom || requestInfo.id == GetRoomState || requestInfo.id == GetPlayersInRoom || requestInfo.id == Update);
}

// Handles Request based on request status
RequestResult RoomMemberRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Check if request relevant
	if (isRequestRelevant(requestInfo))
	{
		switch (requestInfo.id)
		{
		case LeaveRoom:
			return leaveRoom(requestInfo);
		case GetRoomState:
			return getRoomState(requestInfo);
		case Update:
			return roomUpdate(requestInfo);
		case GetPlayersInRoom:
			return getPlayersInRoom(requestInfo);
		}
	}
	else
	{
		// Error
		requestResult = error(requestInfo);
	}

	return requestResult;
}

RequestResult RoomMemberRequestHandler::leaveRoom(Requestinfo requestInfo)
{
	RequestResult requestResult;
	LeaveRoomResponse leaveRoomResponse;
	
	// Remove user from room using room manager
	m_handlerFactory.getRoomManager().getRoom(m_room.getRoomData().id).removeUser(m_user);
	
	// Go to menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = (IRequestHandler*)menuRequestHandler;

	// Succeful leave room status
	leaveRoomResponse.status = TEMP_LEAVE_ROOM_STATUS;

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResponse);

	return requestResult;
}

RequestResult RoomMemberRequestHandler::getRoomState(Requestinfo requestInfo)
{
	RequestResult requestresult;

	GetRoomStateResponse getRoomStateResponse;
	getRoomStateResponseByRoom(m_room, getRoomStateResponse);
	requestresult.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResponse);
	requestresult.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, m_room);

	return requestresult;
}

RequestResult RoomMemberRequestHandler::getPlayersInRoom(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Deserialize request
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buf);

	// Get all the players in a desired room through room manager
	auto room = m_handlerFactory.getRoomManager().getRoom(getPlayersInRoomRequest.roomId);
	std::vector<std::string> players = room.getAllUsers();


	RoomMemberRequestHandler* member = m_handlerFactory.createRoomMemberRequestHandler(m_user, m_room);
	requestResult.newHandler = (IRequestHandler*)member;

	// Create response
	GetPlayersInRoomResponse getPlayersInRoomResponse;
	getPlayersInRoomResponse.status = TEMP_GET_PLAYERS_IN_ROOM_RESPONSE_STATUS;
	getPlayersInRoomResponse.players = players;


	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);

	return requestResult;
}

RequestResult RoomMemberRequestHandler::error(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	ErrorResponse errorResponse;
	errorResponse.message = "Error in Room Member Request Handler.";
	std::cout << "Error in member\n";

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

	// New handler is nullptr - indicates Error
	requestResult.newHandler = nullptr;
	return requestResult;
}

RequestResult RoomMemberRequestHandler::roomUpdate(Requestinfo Requestinfo)
{
	RoomUpdateResponse upd;
	upd.status = m_room.status;

	RequestResult requestResult;
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(upd);
	//(upd.status == 2) ? (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user) : (IRequestHandler*)m_handlerFactory.createRoomMemberRequestHandler(m_user, m_room);
	if (upd.status == 2)
	{
		requestResult.newHandler = (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user);
	}
	else
	{
		requestResult.newHandler = (IRequestHandler*)m_handlerFactory.createRoomMemberRequestHandler(m_user, m_room);
	}
	std::cout << upd.status;
	return requestResult;
}
