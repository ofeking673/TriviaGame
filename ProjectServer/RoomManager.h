#pragma once
#include "Room.h"
#include <map>
#include <random>
#include <chrono>


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
	RandomRoomId(std::map<unsigned int, Room> rooms) : m_rooms(rooms), 
		gen(std::chrono::system_clock::now().time_since_epoch().count()), 
		dist(1, 10000) {}

	unsigned int generateUniqueRoomId() 
	{
		while (true) 
		{
			unsigned int newId = dist(gen);  // Generate a random ID
			if (m_rooms.find(newId) == m_rooms.end()) 
			{
				return newId;  // Return the new ID if it's not already used
			}
			// Generate a new ID if the ID already in use
		}
	}
private:
	// RoomId -> Room
	std::map<unsigned int, Room> m_rooms;

	std::mt19937 gen;
	std::uniform_int_distribution<unsigned int> dist;

};