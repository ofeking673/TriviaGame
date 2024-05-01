#pragma once
#include "Room.h"
#include <time.h>
#include <cstdlib>
#include <map>
#include <random>
#include <chrono>
#include <iostream>


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

	unsigned int generateUniqueRoomId()
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		while (true)
		{
			int newRandom = std::rand() % 10001 + 1; //1-10000
			if (m_rooms.empty() || m_rooms.find(newRandom) == m_rooms.end())
			{
				std::cout << newRandom << std::endl;
				return newRandom;
			}
		}
	}

private:
	// RoomId -> Room
	std::map<unsigned int, Room*> m_rooms;
};