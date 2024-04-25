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

// Login & Signup related
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



// Room & statistics related
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
	// Login & Signup related

	// NOTE:
	// The following 2 functions, gets the buffer of the DATA ONLY (the Json)
	// Without the message code and length.
	// The parsing of message code and length will NOT be here!
	static LoginRequest deserializeLoginRequest(const Buffer bufLoginRequest);
	static SignupRequest deserializeSignupRequest(const Buffer bufSignupRequest);

	static std::string binaryDecoder(std::string buf);


	// Room & statistics related
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(Buffer bufGetPlayersRequest);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer bufJoinRoomRequest);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer bufCreateRoomRequest);
};