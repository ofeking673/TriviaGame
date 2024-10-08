#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

#define LAST_PLAYER_IN_ROOM 1

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser user, Game& game, RequestHandlerFactory& handlerFactory) :
		m_user(user), m_game(game), m_handlerFactory(handlerFactory) {
		m_gameManager = &m_handlerFactory.getGameManager();
	};

	virtual ~GameRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo) override;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) override;
	virtual LoggedUser getUser() override { return m_user; };

private:
	Game& m_game;
	LoggedUser m_user;
	GameManager* m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(Requestinfo requestInfo);
	RequestResult submitAnswer(Requestinfo requestInfo);
	RequestResult getGameResults(Requestinfo requestInfo);
	RequestResult leaveGame(Requestinfo requestInfo);

	RequestResult error(Requestinfo requestInfo);
};