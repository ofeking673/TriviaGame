#pragma once
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

// Login
#define TEMP_LOGIN_RESPONSE_STATUS 100
#define TEMP_FAIL_LOGIN_RESPONSE_STATUS 108

// Signup
#define TEMP_SIGNUP_RESPONSE_STATUS 110
#define TEMP_FAIL_SIGNUP_RESPONSE_STATUS 118

// Logout
#define TEMP_LOGOUT_RESPONSE_STATUS 500
#define TEMP_FAIL_LOGOUT_RESPONSE_STATUS 508

// Getters
#define TEMP_GET_ROOMS_RESPONSE_STATUS 210

#define TEMP_GET_PERSONAL_STATS_RESPONSE_STATUS 220
#define TEMP_GET_HIGH_SCORE_RESPONSE_STATUS 230

#define TEMP_GET_PLAYERS_IN_ROOM_RESPONSE_STATUS 240

// Rooms
#define TEMP_CREATE_ROOM_RESPONSE_STATUS 300
#define TEMP_FAIL_CREATE_ROOM_RESPONSE_STATUS 308

#define TEMP_JOIN_ROOM_RESPONSE_STATUS 310
#define TEMP_FAIL_JOIN_ROOM_RESPONSE_STATUS 318


enum RequestId {
	Login,
	SignUp,
	CreateRoom,
	GetRooms,
	GetPlayersInRoom,
	JoinRoom,
	GetPersonalStats,
	GetHighScores,
	Logout,
	CloseRoom,
	StartGame,
	GetRoomState,
	LeaveRoom,
	end
};

class IRequestHandler;

struct RequestResult {
	Buffer response;
	IRequestHandler* newHandler;
};


struct Requestinfo
{
	RequestId id;
	clock_t time;
	Buffer buf;
};

class IRequestHandler
{
public:
	IRequestHandler() = default;
	virtual ~IRequestHandler() {};

	virtual bool isRequestRelevant(Requestinfo requestInfo) = 0;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) = 0;
};

