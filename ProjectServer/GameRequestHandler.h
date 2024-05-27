#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class GameRequestHandler : public IRequestHandler
{
public:
	// TO-DO maybe change implementation
	GameRequestHandler(LoggedUser user, Game& game, RequestHandlerFactory& handlerFactory) :
		m_user(user), m_game(game), m_handlerFactory(handlerFactory),
		m_gameManager(m_handlerFactory.getGameManager()) {};

	virtual ~GameRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo);
	virtual RequestResult handleRequest(Requestinfo requestInfo);

private:
	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(Requestinfo requestInfo);
	RequestResult submitAnswer(Requestinfo requestInfo);
	RequestResult getGameResults(Requestinfo requestInfo);
	RequestResult leaveGame(Requestinfo requestInfo);

	RequestResult error(Requestinfo requestInfo);
};