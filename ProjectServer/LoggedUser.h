#pragma once
#include <iostream>


class LoggedUser
{
public:
	LoggedUser(std::string name, std::string pass, std::string email) : name(name), pass(pass), email(email) {};

	std::string getName() { return name; };
	std::string getPass() { return pass; };
	std::string getEmail() { return email; };

	void setName(std::string name) { this->name = name; };
	void setPass(std::string pass) { this->pass = pass; };
	void setEmail(std::string email) { this->email = email; };

private:
	std::string name;
	std::string pass;
	std::string email;
};

