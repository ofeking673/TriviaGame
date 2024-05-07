#include "RoomMemberRequestHandler.h"

// Checks if request relevant for handler
bool RoomMemberRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
    return (requestInfo.id == LeaveRoom || requestInfo.id == GetRoomState);
}

// Handles Request based on request status
RequestResult RoomMemberRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Check if request relevant
	if (isRequestRelevant(requestInfo))
	{

		if (requestInfo.id == LeaveRoom)
		{
			// LeaveRoom
			requestResult = leaveRoom(requestInfo);
		}
		else if (requestInfo.id == GetRoomState)
		{
			// GetRoomState
			requestResult = getRoomState(requestInfo);
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

RequestResult RoomMemberRequestHandler::leaveRoom(Requestinfo requestInfo)
{
	RequestResult requestResult;
	LeaveRoomResponse leaveRoomResponse;
	
	// Remove user from room using room manager
	m_handlerFactory.getRoomManager().getRoom(m_room.getRoomData().id).removeUser(m_user);
	
	// Go to menu request handler
	MenuRequestHandler* menuRequestHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	requestResult.newHandler = menuRequestHandler;

	// Succeful leave room status
	leaveRoomResponse.status = TEMP_LEAVE_ROOM_RESPONSE_STATUS;

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(logoutResponse);

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

RequestResult RoomMemberRequestHandler::error(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	ErrorResponse errorResponse;
	errorResponse.message = "Error in Room Member Request Handler.";
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

	// New handler is nullptr - indicates Error
	requestResult.newHandler = nullptr;
	return requestResult;
}
