#pragma once
#include "Room.h"
#include <time.h>
#include <cstdlib>
#include <map>
#include <random>
#include <chrono>
#include <iostream>
#include <memory>

class RoomManager
{
public:
	RoomManager() = default;
	RoomManager(const RoomManager& other);
	~RoomManager() = default;

	bool createRoom(LoggedUser user, RoomData& roomData);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(unsigned int ID);
	std::vector<RoomData> getRooms() const;
	Room& getRoom(unsigned int ID);
	bool doesRoomExist(unsigned int ID);

	unsigned int generateUniqueRoomId();

	//void test(Room* room) { m_rooms.insert({ 0, room }); }

private:
	// RoomId -> Room
	std::map<unsigned int, std::shared_ptr<Room>> m_rooms;
};