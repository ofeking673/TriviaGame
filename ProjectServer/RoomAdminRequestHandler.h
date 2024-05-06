#pragma once
#include "IRequestHandler.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler();
	virtual ~RoomAdminRequestHandler();

	virtual bool isRequestRelevant(Requestinfo requestInfo) override;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) override;


private:
	RequestResult closeRoom(Requestinfo requestInfo);
	RequestResult startGame(Requestinfo requestInfo);
	RequestResult getRoomState(Requestinfo requestInfo);


	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};