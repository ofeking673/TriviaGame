#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <bitset>
#include "Buffer.h"
#include "Room.h"
#include "json.hpp"

using json = nlohmann::json;

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
	unsigned int status;
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
	unsigned int id;
};

// V3
struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeOut;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct RoomUpdateResponse {
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
	static Buffer serializeResponse(const LogoutResponse& logoutResponse); 
	static Buffer serializeResponse(const GetRoomsResponse& getRoomsResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static Buffer serializeResponse(const JoinRoomResponse& joinRoomResponse); 
	static Buffer serializeResponse(const CreateRoomResponse& createRoomResponse); 
	static Buffer serializeResponse(const GetHighScoreResponse& getHighScoreResponse);
	static Buffer serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse);

	// V3
	static Buffer serializeResponse(const CloseRoomResponse& closeRoomResponse);
	static Buffer serializeResponse(const StartGameResponse& startGameResponse);
	static Buffer serializeResponse(const GetRoomStateResponse& getRoomStateResponse);
	static Buffer serializeResponse(const LeaveRoomResponse& leaveRoomResponse);
	static Buffer serializeResponse(const RoomUpdateResponse& roomUpdateResponse);
private:
	static Buffer statusOnlySerializeResponse(const unsigned int status);
	static Buffer jsonObjectSerializer(json j);
};