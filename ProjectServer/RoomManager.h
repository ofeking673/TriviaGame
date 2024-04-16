#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
public:
	RoomManager() = default;
	~RoomManager() = default;

	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(unsigned int ID);
	std::vector<RoomData> getRooms() const;
	Room& getRoom(unsigned int ID);

private:
	// RoomId -> Room
	std::map<unsigned int, Room> m_rooms;
};