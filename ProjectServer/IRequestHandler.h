#pragma once
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#define TEMP_LOGIN_STATUS 10
#define TEMP_SIGNUP_STATUS 20

enum RequestId {
	Login,
	SignUp,
};

struct RequestResult {
	Buffer response;
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
	virtual ~IRequestHandler() = 0;

	virtual bool isRequestRelevant(Requestinfo requestInfo) = 0;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) = 0;
};

