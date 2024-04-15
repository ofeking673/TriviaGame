#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = default;
	virtual ~MenuRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo) { return true; }
	virtual RequestResult HandleRequest(Requestinfo requestInfo) { return RequestResult(); }

private:
};