class RequestHandlerFactory;

#pragma once
#include "IRequestHandler.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room& room, LoggedUser user, RequestHandlerFactory& handlerFactory) :
		m_handlerFactory(handlerFactory), m_room(room), m_user(user), m_roomManager(handlerFactory.getRoomManager()) {};
	
	virtual ~RoomAdminRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo) override;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) override;


private:
	RequestResult closeRoom(Requestinfo requestInfo);
	RequestResult startGame(Requestinfo requestInfo);
	RequestResult getRoomState(Requestinfo requestInfo);
	RequestResult getPlayersInRoom(Requestinfo requestInfo);
	RequestResult error(Requestinfo requestInfo);


	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};