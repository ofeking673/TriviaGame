class RequestHandlerFactory;
class IRequestHandler;

#pragma once
#include "IRequestHandler.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, LoggedUser user, RequestHandlerFactory& handlerFactory) :
		m_handlerFactory(handlerFactory), m_room(room), m_user(user), m_roomManager(handlerFactory.getRoomManager()) {};
	
	virtual ~RoomMemberRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo) override;	
	virtual RequestResult HandleRequest(Requestinfo requestInfo) override;


private:
	RequestResult leaveRoom(Requestinfo requestInfo);
	RequestResult getRoomState(Requestinfo requestInfo);
	RequestResult getPlayersInRoom(Requestinfo requestInfo);
	// -- Inherited form IRequestHandler -- in order to not copy code twice
	RequestResult error(Requestinfo requestInfo);

	RequestResult roomUpdate(Requestinfo Requestinfo);


	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};