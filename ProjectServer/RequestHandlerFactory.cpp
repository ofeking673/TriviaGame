#include "RequestHandlerFactory.h"
#include "GameRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : m_database(database), m_loginManager(new LoginManager(database)),
      m_statisticsManager(new StatisticsManager(database))
{
    if (m_database == nullptr) 
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
    //: m_database(database), m_loginManager(database), m_statisticsManager(database), m_roomManager()
    m_roomManager = new RoomManager();
    m_gameManager = new GameManager(database);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

// Creates login request manager
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

// Return the login manager
LoginManager& RequestHandlerFactory::getLoginManager()
{
    return *m_loginManager;
}

// Creates menu request handler
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, *this);
}

// Return the statistics manager
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return *m_statisticsManager;
}

// Return the room manager
RoomManager& RequestHandlerFactory::getRoomManager()
{
    return *m_roomManager;
}

// Creates room admin request handler
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
    return new RoomAdminRequestHandler(room, user, *this);
}

// Creates room member request handler
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
    return new RoomMemberRequestHandler(room, user, *this);
}

// Creates game request handler
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user)
{
    return new GameRequestHandler(user, m_gameManager->getGameForUser(user), *this);
}

// Return the game manager
GameManager& RequestHandlerFactory::getGameManager()
{
    return *m_gameManager;
}