#pragma once
#include "Room.h"
#include <map>
#include <random>

class RoomManager
{
public:
	RoomManager() = default;
	~RoomManager() = default;

	bool createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(unsigned int ID);
	std::vector<RoomData> getRooms() const;
	Room& getRoom(unsigned int ID);

private:
	// RoomId -> Room
	std::map<unsigned int, Room> m_rooms;
};

class RandomRoomId
{
public:
	RandomRoomId(std::map<unsigned int, Room> rooms) : m_rooms(rooms), gen(rd()), dist(1, 10000) {};
	~RandomRoomId() = default;

	unsigned int generateUniqueRoomId() 
	{
		while (true) 
		{
			unsigned int newId = dist(gen);  // Generate a random number in the range
			// Check if the ID is already used
			if (m_rooms.find(newId) == m_rooms.end())
			{
				return newId;  
			}
			// IF the ID is already used, loop again to generate a new ID
		}
	}
private:
	// RoomId -> Room
	std::map<unsigned int, Room> m_rooms;

	std::random_device rd;  
	std::mt19937 gen;      
	std::uniform_int_distribution<unsigned int> dist;

};