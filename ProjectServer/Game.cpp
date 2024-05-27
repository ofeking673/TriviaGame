#include "Game.h"

Game::Game(std::vector<LoggedUser> players, std::vector<Question> questions, unsigned int gameId) :
	m_questions(questions), m_gameId(gameId)
{
	for (const auto& player : players)
	{
		m_players[player] = GameData{*questions.begin(), 0, 0, 0};
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
/// Submits the answer and updates GameData of current user
/// </summary>
/// <param name="user">Current User</param>
/// <param name="answerId">Answer Id - the answer chosen by user</param>
/// <param name="answerTime">Answer time to current question</param>
void Game::submitAnswer(LoggedUser user, unsigned int answerId, unsigned int answerTime)
{
    if (m_players.find(user) != m_players.end())
    {
        GameData& data = m_players[user];
        if (data.currentQuestion.getCorrectAnswerId() == answerId)
        {
            data.correctAnswerCount++;
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

bool Game::hasPlayer(const LoggedUser& user)
{
    return m_players.find(user) != m_players.end();
}
