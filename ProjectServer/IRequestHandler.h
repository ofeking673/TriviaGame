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
	virtual ~IRequestHandler() = 0;

	virtual bool isRequestRelevant(Requestinfo requestInfo) = 0;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) = 0;
};

