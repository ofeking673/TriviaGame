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

#define TEMP_GET_ROOM_STATE_STATUS 250

// Rooms
#define TEMP_CREATE_ROOM_RESPONSE_STATUS 300
#define TEMP_FAIL_CREATE_ROOM_RESPONSE_STATUS 308

#define TEMP_JOIN_ROOM_RESPONSE_STATUS 310
#define TEMP_FAIL_JOIN_ROOM_RESPONSE_STATUS 318

// Room user request handlers
#define TEMP_LEAVE_ROOM_STATUS 400
#define TEMP_ROOM_CLOSE_STATUS 410
#define TEMP_ROOM_START_STATUS 420

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
	Update,
	Error69 = 69
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

protected:
	//for room request handlers
	void getRoomStateResponseByRoom(Room m_room, GetRoomStateResponse& resp) {
		RoomData rm = m_room.getRoomData();

		resp.answerTimeOut = rm.timePerQuestion;
		resp.hasGameBegun = rm.isActive;
		resp.players = m_room.getAllUsers();
		resp.questionCount = rm.numOfQuestionsInGame;
		resp.status = TEMP_GET_ROOM_STATE_STATUS;
		
	};
};

