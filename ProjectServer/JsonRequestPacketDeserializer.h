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


/*
struct ErrorResponse
{
	// error messasge
	std::string message;
};

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
*/

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
};