#pragma once
#include <string>
#include <iostream>
#include <bitset>
#include "Buffer.h"
#include "Room.h"

// Struct of error response
struct ErrorResponse
{
	// error messasge
	std::string message;
};

// Login & Signup related
 
// Struct of login response
struct LoginResponse
{
	// login status
	unsigned int status;
};

// Struct of signup response
struct SignupResponse
{
	// signup status
	unsigned int status;
};

// Room & statistics related
struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};


// Static class to serialize json response packets
class JsonResponsePacketSerializer
{
public:
	// Error
	static Buffer serializeResponse(const ErrorResponse& errorResponse);

	// Login & Signup related
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);

	static std::string encodeBinary(std::string encodeStr);


	// Room & statistics related
	static Buffer serializeResponse(const LogoutResponse& logoutResponse); //________
	static Buffer serializeResponse(const GetRoomsResponse& getRoomsResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static Buffer serializeResponse(const JoinRoomResponse& joinRoomResponse); //_____
	static Buffer serializeResponse(const CreateRoomResponse& createRoomResponse); //_____
	static Buffer serializeResponse(const GetHighScoreResponse& getHighScoreResponseResponse);
	static Buffer serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse);

private:
	static Buffer statusOnlySerializeResponse(const unsigned int status);
};