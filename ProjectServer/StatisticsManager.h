#pragma once
#include "DatabaseAccess.h"
#include <iostream>
#include <vector>

class StatisticsManager
{
public:
    // Public method to access the single instance
    static StatisticsManager& getInstance();

    // Delete copy constructors
    StatisticsManager(const StatisticsManager&) = delete;
    StatisticsManager& operator=(const StatisticsManager&) = delete;

	~StatisticsManager();

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
	void addQuestion(std::string question, std::vector<std::string> answers);

private:
    // Private constructor
    StatisticsManager(IDatabase* database);

    // Static method to initialize the singleton instance
    static void initSingleton();

    // Pointer to the single instance
    static StatisticsManager* instance;

    // Flag to ensure the instance is only created once
    static std::once_flag initInstanceFlag;

	IDatabase* m_database;
};