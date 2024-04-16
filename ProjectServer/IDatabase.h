#pragma once
#include <string>
#include <map>
#include "Question.h"
#include <list>

#define FILENAME "database.sql"

class IDatabase
{
public:
	virtual ~IDatabase() {};

	// Login & Signup related
	virtual void open(std::string fileName) = 0;
	virtual void close() = 0;

	virtual void InitDb() = 0;

	virtual bool doesUserExist(std::string name) = 0;
	virtual void addUser(std::string name, std::string pass, std::string email) = 0;
	virtual bool isPassCorrect(std::string name, std::string pass) = 0;
	virtual std::map<std::string, std::string> getAccountData(std::string name) = 0;

	// Room & statistics related
	virtual std::list<Question> getQuestions(int roomId /*?*/) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual int getPlayerScore(std::string username);
	std::vector<std::string> getHighScores();
};