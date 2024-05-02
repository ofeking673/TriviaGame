#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory) :m_handlerFactory(handlerFactory), m_loginManager(handlerFactory.getLoginManager()) {}
	virtual ~LoginRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo requestInfo);
	virtual RequestResult HandleRequest(Requestinfo requestInfo);

private:
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;

	RequestResult login(Requestinfo requestInfo);
	RequestResult signup(Requestinfo requestInfo);
	RequestResult error(Requestinfo requestInfo);
};