#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : m_database(database), m_loginManager(database)
{
    if (m_database == nullptr) 
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
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
