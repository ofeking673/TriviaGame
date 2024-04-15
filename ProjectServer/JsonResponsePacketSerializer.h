#pragma once
#include <string>
#include <iostream>
#include <bitset>
#include "Buffer.h"


// Struct of error response
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


// Static class to serialize json response packets
class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);

	static std::string encodeBinary(std::string encodeStr);
};