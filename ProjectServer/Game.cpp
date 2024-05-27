#include "Game.h"

Game::Game(std::vector<LoggedUser> players, std::vector<Question> questions, unsigned int gameId, unsigned int timeLimit) :
	m_questions(questions), m_gameId(gameId), m_timeLimit(timeLimit)
{
	for (const auto& player : players)
	{
		m_players[player] = GameData{*questions.begin(), 0, 0, 0, 0};
	}
}

Game::~Game()
{
    // Removing all players from game and writing their scores in DB
    for (const auto& player : m_players)
    {
        removePlayer(player.first);
    }
}

/// <summary>
/// Returns the current question that the user will have to answer to
/// </summary>
/// <param name="user">Current User</param>
/// <returns>Question</returns>
Question Game::getQuestionForUser(LoggedUser user)
{
	if (m_players.find(user) != m_players.end())
	{
		return m_players[user].currentQuestion;
	}
	else
	{
		throw std::invalid_argument("User not found in the game");
	}
}

/// <summary>
/// Submits the answer.
/// Updates GameData of current user and his score.
/// </summary>
/// <param name="user">Current User</param>
/// <param name="answerId">Answer Id - the answer chosen by user</param>
/// <param name="answerTime">Answer time to current question</param>
/// <returns>Returns the current score of user</returns>
unsigned int Game::submitAnswer(LoggedUser user, unsigned int answerId, double answerTime)
{
    if (m_players.find(user) != m_players.end())
    {
        GameData& data = m_players[user];
        if (data.currentQuestion.getCorrectAnswerId() == answerId)
        {
            data.correctAnswerCount++;
            data.score += calculateScore(answerTime); // Update score
        }
        else
        {
            data.wrongAnswerCount++;
        }
        data.averageAnswerTime = ((data.averageAnswerTime * (data.correctAnswerCount + data.wrongAnswerCount - 1)) + answerTime) / (data.correctAnswerCount + data.wrongAnswerCount);

        // Move to the next question
        auto it = std::find(m_questions.begin(), m_questions.end(), data.currentQuestion);
        if (it != m_questions.end() && ++it /*Next question*/ != m_questions.end())
        {
            data.currentQuestion = *it;
        }
        else
        {
            // Empty Question to indicate no more questions left
            data.currentQuestion = Question();
        }

        // Return the current score of user
        return data.score;
    }
    else
    {
        throw std::invalid_argument("User not found in the game");
    }
}

void Game::removePlayer(LoggedUser user)
{
    auto it = m_players.find(user);
    if (it != m_players.end()) 
    {
        // Player stays in room but being removed from the game.
        // Therefore, we can give the list of scores for the players
        // who left in the middle of the game as well.

        // Game data of player is being put in DB
        sumitGameStatsToDB(it->second);
        m_players.erase(it);
    }
    else 
    {
        throw std::invalid_argument("User not found in the game");
    }
}

unsigned int Game::getGameId() const
{
    return m_gameId;
}

std::vector<std::pair<LoggedUser, GameData>> Game::getOrderedPlayersByScore() const
{
    std::vector<std::pair<LoggedUser, GameData>> orderedPlayers(m_players.begin(), m_players.end());

    std::sort(orderedPlayers.begin(), orderedPlayers.end(), compareByScore);

    return orderedPlayers;
}


bool Game::hasPlayer(const LoggedUser& user) const
{
    return m_players.find(user) != m_players.end();
}

unsigned int Game::calculateScore(unsigned int answerTime) const
{
    if (answerTime >= m_timeLimit)
    {
        return 0;
    }
    return static_cast<unsigned int>(100 * (1.0 - static_cast<double>(answerTime) / m_timeLimit));
}
bool Game::compareByScore(const std::pair<LoggedUser, GameData>& a, const std::pair<LoggedUser, GameData>& b)
{
    return a.second.score > b.second.score;
}
