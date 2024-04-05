#pragma once
#include "IRequestHandler.h"
#include <iostream>

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	LoginRequestHandler(std::string name, std::string pass, std::string email) : IRequestHandler(), name(name), pass(pass), email(email) {};

	virtual void HandleRequest() override {
		
	};
private:
	std::string name;
	std::string pass;
	std::string email;
};