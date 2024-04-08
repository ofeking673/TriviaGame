#pragma once
#include <iostream>
#include "JsonRequestPacketDeserializer.h"

enum RequestId {
	Login,
	SignUp,
};

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
	virtual bool isRequestRelevant(Requestinfo req) = 0;
	virtual void HandleRequest() = 0;
};

