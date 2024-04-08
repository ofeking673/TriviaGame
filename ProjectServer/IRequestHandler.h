#pragma once
#include <iostream>
#include "JsonRequestPacketDeserializer.h"

enum packetType {
	Login,
	SignUp,
	Error
};


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Requestinfo req) = 0;
	virtual void HandleRequest() = 0;
};

