#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include <map>
#include <iostream>


struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount = 0;
	unsigned int wrongAnswerCount = 0;
	double averageAnswerTime = 0.0;
	unsigned int score = 0;
};

class Game
{
public:
	Game(std::vector<LoggedUser> players, std::vector<Question> questions, unsigned int gameId, unsigned int timeLimit);
	~Game();

	Question getQuestionForUser(LoggedUser user);
	unsigned int submitAnswer(LoggedUser user, unsigned int answerId, double answerTime);
	void removePlayer(LoggedUser user);

	unsigned int getGameId() const;

	// Returns ordered vector of users and their scores to show in game results
	std::vector<std::pair<LoggedUser, GameData>> getOrderedPlayersByScore() const;

	bool hasPlayer(const LoggedUser& user) const;

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
	unsigned int m_timeLimit;

	// Score formula:
	// 100 * (1 - answerTime / timeLimit)
	unsigned int calculateScore(unsigned int answerTime) const;

	bool compareByScore(const std::pair<LoggedUser, GameData>& a, const std::pair<LoggedUser, GameData>& b);
};