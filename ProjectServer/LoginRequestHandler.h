#pragma once
#include "IRequestHandler.h"
#include <iostream>

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	virtual ~LoginRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo) = 0;
	virtual RequestResult HandleRequest(Requestinfo requestInfo) = 0;

private:
};