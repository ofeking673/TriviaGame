#pragma once
#include "IRequestHandler.h"
#include <iostream>

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;

	virtual bool isRequestRelevant(Requestinfo req) override {
		return  (req.id == Login || req.id == SignUp);
	};

	virtual void HandleRequest() override {
		//HELP: my brain hurts i dont even know when to start
	};
private:
};