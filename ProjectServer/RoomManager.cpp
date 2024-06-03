#include "RoomManager.h"

// Initialize static members
RoomManager* RoomManager::instance = nullptr;
std::once_flag RoomManager::initInstanceFlag;

RoomManager& RoomManager::getInstance()
{
    std::call_once(initInstanceFlag, &RoomManager::initSingleton);
    return *instance;
}

// Creates a new room and add it to the rooms map
bool RoomManager::createRoom(LoggedUser user, RoomData& roomData)
{
    // Hopefuly will work :)

    // Generate unique room id
    roomData.id = generateUniqueRoomId();

    // Check if a room with the same ID already exists
    if (m_rooms.find(roomData.id) != m_rooms.end())
    {
        return false; // Room already exists
    }

    // Create a new room with the given data 
    std::shared_ptr<Room> newRoom = std::make_shared<Room>(roomData);
    // Add the first user to the room
    newRoom->addUser(user);

    // Insert the new room into the map 
    m_rooms[roomData.id] = newRoom;
    return true;
}

// Remove the room from the map
void RoomManager::deleteRoom(unsigned int ID)
{
    m_rooms.erase(ID);
}

// Gets room state (isActive).
unsigned int RoomManager::getRoomState(unsigned int ID)
{
    auto it = m_rooms.find(ID);
    if (it != m_rooms.end())
    {
        return it->second->getRoomData().isActive;
    }
    // Room not found
    return 0;
}

// Gets a vector of all rooms data
std::vector<RoomData> RoomManager::getRooms() const
{
    std::vector<RoomData> roomList;
    for (const auto& pair : m_rooms)
    {
        roomList.push_back(pair.second->getRoomData());
    }
    return roomList;
}

// Return a reference to room
Room& RoomManager::getRoom(unsigned int ID)
{
    return *(m_rooms[ID]);
}

bool RoomManager::doesRoomExist(unsigned int ID)
{
    return (m_rooms.find(ID) != m_rooms.end());
}

// Generate a unique room id
unsigned int RoomManager::generateUniqueRoomId()
{
    srand(time(NULL));

    unsigned int newId;
    do 
    {
        newId = rand() % 10000 + 1;  // 1-10000
    } while (m_rooms.find(newId) != m_rooms.end());  // Check if the ID is already used

    return newId; 
}

Room& RoomManager::getRoomForUser(const LoggedUser& user)
{
    for (auto& room : m_rooms)
    {
        if (room.second->hasPlayer(user))
        {
            return *room.second;
        }
    }
    throw std::runtime_error("User not found in any game");
}

void RoomManager::initSingleton()
{
    instance = new RoomManager();
}

