#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);

private:
	// RoomId -> Room
	std::map<int, Room> m_rooms;
};