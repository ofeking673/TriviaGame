#pragma once
#include "IRequestHandler.h"
#include <iostream>

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	virtual ~LoginRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo);
	virtual RequestResult HandleRequest(Requestinfo requestInfo);

private:
};