#pragma once
#include "Game.h"
#include "DatabaseAccess.h"
#include "Room.h"

class GameManager
{
public:
	// Public method to access the single instance
	static GameManager& getInstance();

	// Delete copy constructor and assignment operator
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	~GameManager();

	Game createGame(const Room& room);
	void deleteGame(unsigned int gameId);

	Game& getGameForUser(const LoggedUser& user);

	void submitGameStatsToDB(const std::string& username,const GameData& gameData);
private:

	// Private constructors
	GameManager(IDatabase* database);
	GameManager() = default;

	// Static method to initialize the singleton instance
	static void initSingleton();

	// Pointer to the single instance
	static GameManager* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;

	IDatabase* m_database;
	std::vector<Game> m_games;

	unsigned int generateUniqueGameId();
};