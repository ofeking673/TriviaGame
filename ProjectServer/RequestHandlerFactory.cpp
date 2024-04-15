#include "RequestHandlerFactory.h"

// Creates login request manager
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return &LoginRequestHandler(*this);
}

// Return the login manager
LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}
