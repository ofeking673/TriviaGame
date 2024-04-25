#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RequestHandlerFactory& handlerFactory) : m_user(user), m_handlerFactory(handlerFactory) {};
	virtual ~MenuRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo);
	virtual RequestResult HandleRequest(Requestinfo requestInfo);

	RequestResult signout(Requestinfo requestInfo);
	RequestResult getRooms(Requestinfo requestInfo);
	RequestResult getPlayersInRoom(Requestinfo requestInfo);
	RequestResult getPersonalStats(Requestinfo requestInfo);
	RequestResult getHighScore(Requestinfo requestInfo);
	RequestResult joinRoom(Requestinfo requestInfo);
	RequestResult createRoom(Requestinfo requestInfo);

	RequestResult error(Requestinfo requestInfo);

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
};