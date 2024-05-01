#include "RoomManager.h"

// Creates a new room and add it to the rooms map
bool RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
    std::cout << roomData.id << std::endl;
    // If the given room ID is 0 -> generate a unique id
    if (roomData.id == 0)
    {
        roomData.id = generateUniqueRoomId();
    }
    // Check if a Room with the given ID doesnt exist
    if (m_rooms.empty() || m_rooms.find(roomData.id) == m_rooms.end())
    {
        Room* curRoom = new Room(roomData);
        std::cout << "HASAMA";
        m_rooms[roomData.id] = curRoom;
        std::cout << "NOT HASAMA";
        //m_rooms.emplace(roomData.id, Room(roomData));

        // Add the user to the room
        m_rooms[roomData.id]->addUser(user);

        return true;
    }
    // Unable to create room
    return false;
}

// Remove the room from the map
void RoomManager::deleteRoom(unsigned int ID)
{
    /*TO-DO delete from DB*/
    m_rooms.erase(ID);
}

// Gets room state (isActive).
unsigned int RoomManager::getRoomState(unsigned int ID)
{
    if (m_rooms.find(ID) != m_rooms.end())
    {
        return m_rooms[ID]->getRoomData().isActive;
    }
    
    // Room Not found
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
