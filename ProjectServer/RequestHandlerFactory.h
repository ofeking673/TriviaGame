#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"

// TO-DO manage circular dependencies when adding handlers
class GameRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class MenuRequestHandler;
class LoginRequestHandler;


class RequestHandlerFactory
{
public:

	// Public method to access the single instance
	static RequestHandlerFactory& getInstance(IDatabase* database);

	// Delete copy constructor and assignment operator
	RequestHandlerFactory(const RequestHandlerFactory&) = delete;
	RequestHandlerFactory& operator=(const RequestHandlerFactory&) = delete;

	~RequestHandlerFactory();

	// Login & Signup related
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	// Room & statistics related
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	// Inside Room related
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room& room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room& room);
	
	// Game related
	GameRequestHandler* createGameRequestHandler(LoggedUser user);
	GameManager& getGameManager();
	
private:
	// TO-DO: Need to change - when adding new managers
	RequestHandlerFactory(IDatabase* database);

	// Static method to initialize the singleton instance
	static void initSingleton(IDatabase* database);

	// Pointer to the single instance
	static RequestHandlerFactory* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;


	IDatabase* m_database;

	// Login & Signup related
	LoginManager& m_loginManager;

	// Room & statistics related
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;

	// Game related
	GameManager& m_gameManager;
};