#pragma once
#include "Room.h"
#include <time.h>
#include <cstdlib>
#include <map>
#include <random>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>

class RoomManager
{
public:
	// Public method to access the single instance
	static RoomManager& getInstance();

	// Delete copy constructors
	RoomManager(const RoomManager& other) = delete;
	RoomManager& operator=(const RoomManager& other) = delete;

	~RoomManager() = default;

	bool createRoom(LoggedUser user, RoomData& roomData);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(unsigned int ID);
	std::vector<RoomData> getRooms() const;
	Room& getRoom(unsigned int ID);
	bool doesRoomExist(unsigned int ID);

	unsigned int generateUniqueRoomId();

	Room& getRoomForUser(const LoggedUser& user);

private:
	// Private ctor
	RoomManager() = default;

	// Static method to initialize the singleton instance
	static void initSingleton();

	// Pointer to the single instance
	static RoomManager* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;

	// RoomId -> Room
	std::map<unsigned int, std::shared_ptr<Room>> m_rooms;
};