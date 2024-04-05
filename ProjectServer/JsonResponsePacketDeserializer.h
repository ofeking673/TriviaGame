#pragma once
#include <ctime>
#include "JsonResponsePacketSerializer.h"
#include "json.hpp"


using json = nlohmann::json;

enum statusValues
{
	OK = 1,
	BAD = 999
};

struct Requestinfo {
	int status;
	clock_t time;
	Buffer buf;
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

class JsonResponsePacketDeserializer
{
public:
	static ErrorResponse deserializeErrorResponse(const Requestinfo info);
	static LoginResponse deserializeLoginResponse(const Requestinfo info);
	static SignupResponse deserializeSignupResponse(const Requestinfo info);

	static json getJsonFromString(std::vector<unsigned char> x);

};

