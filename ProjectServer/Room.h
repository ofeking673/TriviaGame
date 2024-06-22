#pragma once
#include "LoggedUser.h"
#include <iostream>
#include <vector>

// isMatchmaking values
#define TO_MATCHMAKING 1
#define NOT_TO_MATCHMAKING 0

//waitingForMatchmaking values
#define WAITING 1
#define FOUND_USER 0


// Struct to represent data of room
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
	unsigned int isMatchmaking;
	unsigned int waitingForMatchmaking;
};


class Room
{
public:
	Room(const RoomData& roomData) : m_metadata(roomData), status(0) {};
	~Room() = default;

	bool addUser(const LoggedUser& user);
	bool removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers() const;
	void startGame(LoggedUser& owner);

	RoomData getRoomData() const;
	int status;

	bool hasPlayer(const LoggedUser& user) const;
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};