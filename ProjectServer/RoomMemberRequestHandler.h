#pragma once
#include "IRequestHandler.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler();
	virtual ~RoomMemberRequestHandler();

	virtual bool isRequestRelevant(Requestinfo requestInfo) override;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) override;


private:
	RequestResult leaveRoom(Requestinfo requestInfo);
	RequestResult getRoomState(Requestinfo requestInfo);


	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};