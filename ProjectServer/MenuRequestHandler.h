#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	virtual ~MenuRequestHandler();

	virtual bool isRequestRelevant(Requestinfo requestInfo);
	virtual RequestResult HandleRequest(Requestinfo requestInfo);

	RequestResult signuot(Requestinfo requestInfo);
	RequestResult getRooms(Requestinfo requestInfo);
	RequestResult getPlayersInRoom(Requestinfo requestInfo);
	RequestResult getPersonalStats(Requestinfo requestInfo);
	RequestResult getHighScore(Requestinfo requestInfo);
	RequestResult joinRoom(Requestinfo requestInfo);
	RequestResult createRoom(Requestinfo requestInfo);

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
};