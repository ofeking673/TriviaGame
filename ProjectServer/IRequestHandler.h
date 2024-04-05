#pragma once
#include <iostream>
class IRequestHandler
{
public:
	unsigned int status;
	std::string errmsg;

	virtual void HandleRequest() = 0;
};

