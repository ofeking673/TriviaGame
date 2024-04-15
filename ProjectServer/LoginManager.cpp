#include "LoginManager.h"

LoginManager::LoginManager(std::string fileName) : m_database(new DatabaseAccess(fileName)) {}

bool LoginManager::login(std::string name, std::string pass)
{
    if (db.doesUserExist(name))
    {
        if (db.isPassCorrect(name, pass))
        {
            auto data = db.getAccountData(name);
            LoggedUser* logged = new LoggedUser(name, pass, data["email"]);
            m_loggedUsers.push_back(logged);
            return true;
        }
    }
    return false;
}

bool LoginManager::signup(std::string name, std::string pass, std::string email)
{
    if (!db.doesUserExist(name))
    {
        db.addUser(name, pass, email);
        m_loggedUsers.push_back(new LoggedUser(name, pass, email));
        return true;
    }
    return false;
}

bool LoginManager::logOut(std::string name)
{
    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            delete* it;
            m_loggedUsers.erase(it);
            return true;
        }
    }
    return false;
}
