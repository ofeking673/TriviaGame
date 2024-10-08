#include "RequestHandlerFactory.h"
#include "GameRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"

// Initialize static members
RequestHandlerFactory* RequestHandlerFactory::instance = nullptr;
std::once_flag RequestHandlerFactory::initInstanceFlag;

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    :   m_database(database),
        m_loginManager(LoginManager::getInstance()),
        m_statisticsManager(StatisticsManager::getInstance()),
        m_roomManager(RoomManager::getInstance()),
        m_gameManager(GameManager::getInstance())
{
    if (m_database == nullptr) 
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
}

void RequestHandlerFactory::initSingleton(IDatabase* database)
{
    instance = new RequestHandlerFactory(database);
}

RequestHandlerFactory& RequestHandlerFactory::getInstance(IDatabase* database)
{
    std::call_once(initInstanceFlag, &RequestHandlerFactory::initSingleton, database);
    return *instance;
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
    return m_loginManager.getInstance();
}

// Creates menu request handler
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, *this);
}

// Return the statistics manager
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager.getInstance();
}

// Return the room manager
RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager.getInstance();
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
    return new GameRequestHandler(user, m_gameManager.getGameForUser(user), *this);
}

// Return the game manager
GameManager& RequestHandlerFactory::getGameManager()
{
    return m_gameManager.getInstance();
}