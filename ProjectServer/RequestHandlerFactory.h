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
	// TO-DO: Need to change - when adding new managers
	RequestHandlerFactory(IDatabase* database);
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
	IDatabase* m_database;

	// Login & Signup related
	LoginManager* m_loginManager;

	// Room & statistics related
	RoomManager* m_roomManager;
	StatisticsManager* m_statisticsManager;

	// Game related
	GameManager* m_gameManager;
};