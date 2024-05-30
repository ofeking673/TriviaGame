#pragma once
#include "Game.h"
#include "DatabaseAccess.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(IDatabase* database);
	GameManager() = default;
	~GameManager();

	Game createGame(const Room& room);
	void deleteGame(unsigned int gameId);

	Game& getGameForUser(const LoggedUser& user);

	void submitGameStatsToDB(const std::string& username,const GameData& gameData);
private:
	IDatabase* m_database;
	std::vector<Game> m_games;

	unsigned int generateUniqueGameId();
};