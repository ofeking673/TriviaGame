#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

// TO-DO circular dependencies V3
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
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room room);

private:
	IDatabase* m_database;

	// Login & Signup related
	LoginManager* m_loginManager;

	// Room & statistics related
	RoomManager* m_roomManager;
	StatisticsManager* m_statisticsManager;

};