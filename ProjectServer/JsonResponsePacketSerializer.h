#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <bitset>
#include "Buffer.h"
#include "Room.h"
#include "json.hpp"

#define WAIT_IN_ROOM__ROOM_UPDATE_RESPONSE_STATUS 0
#define GAME_STARTS__ROOM_UPDATE_RESPONSE_STATUS 1
#define LEAVE__ROOM_UPDATE_RESPONSE_STATUS 2

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
	unsigned int isMatchmaking;
	unsigned int waitingForAnotherUser;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct RoomUpdateResponse 
{
	unsigned int status;
};

// Game related
struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	//		answer number, answer sentence
	std::vector<std::string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
	unsigned int score;
};

// Game Results
struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;
	unsigned int score;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};

struct AddQuestionResponse 
{
	unsigned int status;
};

struct StartMatchmakingResponse
{
	unsigned int status;
	unsigned int roomId;
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

	// Game related
	static Buffer serializeResponse(const GetGameResultsResponse& getGameResultsResponse);
	static Buffer serializeResponse(const SubmitAnswerResponse& submitAnswerResponse);
	static Buffer serializeResponse(const GetQuestionResponse& getQuestionResponse);
	static Buffer serializeResponse(const LeaveGameResponse& leaveGameResponse);

	static Buffer serializeResponse(const AddQuestionResponse& addQuestionResponse);

	// Matchmaking
	static Buffer serializeResponse(const StartMatchmakingResponse& startMatchmakingResponse);

private:
	static Buffer statusOnlySerializeResponse(const unsigned int status);
	static Buffer jsonObjectSerializer(json j);
};