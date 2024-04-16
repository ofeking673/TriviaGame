#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	// TO-DO: Need to change - added room and statistics
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	// Login & Signup related
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	// Room & statistics related
	MenuRequestHandler* createMenuRequestHandler(LoggedUser);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

private:
	IDatabase* m_database;

	// Login & Signup related
	LoginManager m_loginManager;

	// Room & statistics related
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;

};