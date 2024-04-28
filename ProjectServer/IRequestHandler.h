#pragma once
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#define TEMP_LOGIN_STATUS 10
#define TEMP_FAIL_LOGIN_STATUS 18
#define TEMP_SIGNUP_STATUS 20
#define TEMP_FAIL_SIGNUP_STATUS 28


enum RequestId {
	Login,
	SignUp,
	CreateRoom,
	GetRooms,
	GetPlayersInRoom,
	JoinRoom,
	GetStatistics,
	Logout
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

