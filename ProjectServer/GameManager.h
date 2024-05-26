#pragma once
#include "Game.h"
#include "DatabaseAccess.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(IDatabase* database);
	~GameManager();

	Game createGame(Room room);
	void deleteGame(unsigned int gameId);

private:
	IDatabase* m_database;
	std::vector<Game> m_games;

	unsigned int generateUniqueGameId();
};