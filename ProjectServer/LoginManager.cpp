#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database)
    : m_database(database)
{
    if (m_database == nullptr)
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
}

LoginManager::~LoginManager()
{
    m_loggedUsers.clear();
}


bool LoginManager::login(std::string name,std::string pass)
{
    // Check if the user exists
    if (!m_database->doesUserExist(name))
    {
        return false; // User does not exist
    }

    // Check if the password is correct
    if (!m_database->isPassCorrect(name, pass))
    {
        return false; 
    }

    if (std::find_if(m_loggedUsers.begin(), m_loggedUsers.end(), [&name](const LoggedUser& user) {
        return user.getUsername() == name;
        }) != m_loggedUsers.end())
    {
        return false; // User is already logged in
    }

    // User authentication successful and not already logged in
    m_loggedUsers.push_back(LoggedUser(name));
    return true;
}


bool LoginManager::signup(std::string name, std::string pass, std::string email)
{
    if (!m_database->doesUserExist(name))
    {
        m_database->addUser(name, pass, email);
        LoggedUser user(name);
        m_loggedUsers.push_back(user);
        return true;
    }
    return false;
}

bool LoginManager::logout(std::string name)
{
    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
    {
        if (it->getUsername() == name)
        {
            m_loggedUsers.erase(it);
            return true;
        }
    }
    return false;
}
