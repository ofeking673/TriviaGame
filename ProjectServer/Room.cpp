#include "Room.h"

// Adds user to room
void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);
}

// Removes a user from the room
void Room::removeUser(const LoggedUser& user)
{
    for (auto it = m_users.begin(); it != m_users.end(); it++)
    {
        if (it->getUsername() == user.getUsername())
        {
            m_users.erase(it);
            break;
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

RoomData Room::getRoomData() const
{
    return m_metadata;
}


