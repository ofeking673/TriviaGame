#pragma once
#include "LoggedUser.h"
#include <iostream>
#include <vector>

// Struct to represent data of room
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};


class Room
{
public:
	Room(const RoomData& roomData) : m_metadata(roomData) {};
	~Room() = default;

	bool addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers() const;

	RoomData getRoomData() const;

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};