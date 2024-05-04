#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : m_database(database), m_loginManager(LoginManager(database)), m_statisticsManager(StatisticsManager(database))
{
    if (m_database == nullptr) 
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
    //: m_database(database), m_loginManager(database), m_statisticsManager(database), m_roomManager()
    m_roomManager = new RoomManager();
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
    return m_loginManager;
}

// Creates menu request handler
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, *this);
}

// Return the statistics manager
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}

// Return the room manager
RoomManager& RequestHandlerFactory::getRoomManager()
{
    return *m_roomManager;
}
