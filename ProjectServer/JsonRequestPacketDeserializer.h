#pragma once
#include <ctime>
//#include "JsonResponsePacketSerializer.h"
#include "Buffer.h"
#include "json.hpp"
#include <bitset>
#include <iostream>


using json = nlohmann::json;

enum statusValues
{
	OK = 1,
	BAD = 999
};

// Login and signup requests related
struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};



// Rooms requests realted
struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionsCount;
	unsigned int answerTimeout;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};



class JsonRequestPacketDeserializer
{
public:
	// NOTE:
	// The following 2 functions, gets the buffer of the DATA ONLY (the Json)
	// Without the message code and length.
	// The parsing of message code and length will NOT be here!
	static LoginRequest deserializeLoginRequest(const Buffer bufLoginRequest);
	static SignupRequest deserializeSignupRequest(const Buffer bufSignupRequest);

	static std::string binaryDecoder(std::string buf);


	// Room requests related
	GetPlayersInRoomRequest deserializeGetPlayersRequest(Buffer bufGetPlayersRequest);
	JoinRoomRequest deserializeJoinRoomRequest(Buffer bufJoinRoomRequest);
	CreateRoomRequest deserializeCreateRoomRequest(Buffer bufCreaterRoomRequest);
};