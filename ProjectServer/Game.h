#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include <map>
#include <iostream>


struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;
};

class Game
{
public:
	Game(std::vector<LoggedUser> players, std::vector<Question> questions, unsigned int gameId);
	~Game();

	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int answerId, double answerTime);
	void removePlayer(LoggedUser user);

	unsigned int getGameId() const;

	bool hasPlayer(const LoggedUser& user) const;

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;

	// TO-DO implement function when working on DB
	void sumitGameStatsToDB(GameData gameData);
};