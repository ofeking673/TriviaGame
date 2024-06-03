#pragma once
#include "IDatabase.h"
#include <iostream>
#include <vector>

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database);
	~StatisticsManager();

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
	void addQuestion(std::string question, std::vector<std::string> answers);

private:
	IDatabase* m_database;
};