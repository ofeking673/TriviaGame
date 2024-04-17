#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database)
{
    if (m_database == nullptr)
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
}

StatisticsManager::~StatisticsManager()
{
}

// Gets a vector of 5 best scores through database
std::vector<std::string> StatisticsManager::getHighScore()
{
    return m_database->getHighScores();
}

// Gets a vector of user statistics
// IMPORTANT!!!
// The vector will be in the following format
//playerScore, numOfPlayerGames, numOfTotalAnswers, numOfCorrectAnswers, playerAverageAnswerTime
std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    std::vector<std::string> userStatistics;
    userStatistics.push_back(std::to_string(m_database->getPlayerScore(username)));
    userStatistics.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));
    userStatistics.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
    userStatistics.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
    userStatistics.push_back(std::to_string(m_database->getPlayerAverageAnswerTime(username)));

    return userStatistics;
}


