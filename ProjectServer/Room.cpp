#include "Room.h"
#include "Room.h"

// Adds user to room
bool Room::addUser(const LoggedUser& user)
{
    if (m_metadata.maxPlayers > m_users.size())
    {
        m_users.push_back(user);
        return true;
    }
    return false;

}

// Removes a user from the room
void Room::removeUser(const LoggedUser& user)
{
    for (auto it = m_users.begin(); it != m_users.end(); it++)
    {
        if (it->getUsername() == user.getUsername())
        {
            m_users.erase(it);
            return;
        }
    }
}

// Gets all users logged in the room
std::vector<std::string> Room::getAllUsers() const
{
    std::vector<std::string> usernames;
    for (const auto& user : m_users)
    {
        usernames.push_back(user.getUsername());
    }
    return usernames;
}

void Room::startGame(LoggedUser& owner)
{
    if (m_users[0].getUsername() == owner.getUsername())
    {
        this->m_metadata.isActive = true;
    }
}

RoomData Room::getRoomData() const
{
    return m_metadata;
}

bool Room::hasPlayer(const LoggedUser& user) const
{
    for (const auto& u : m_users) 
    {
        if (u.getUsername() == user.getUsername())
        {
            return true;
        }
    }
    return false;
}


