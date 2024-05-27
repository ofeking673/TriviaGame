#include "GameManager.h"

GameManager::GameManager(IDatabase* database) 
	: m_database(database)
{
    if (m_database == nullptr)
    {
        throw std::invalid_argument("Invalid Database pointer");
    }
}

GameManager::~GameManager()
{
}

Game GameManager::createGame(const Room& room)
{
    // Get users list
    std::vector<std::string> usersStr = room.getAllUsers();

    std::vector<LoggedUser> players;
    for (const auto& userStr : usersStr)
    {
        LoggedUser player(userStr);
        players.push_back(player);
    }

    // Get questions from DB
    std::list<Question> questionList = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);
    // Convert to vector
    std::vector<Question> questions(questionList.begin(), questionList.end());

    // Generate unique game id
    unsigned int gameId = generateUniqueGameId();


    Game newGame(players, questions, gameId);

    m_games.push_back(newGame);
    
    return newGame;
}

void GameManager::deleteGame(unsigned int gameId)
{
    // Find the game with the given ID and remove it
    for (auto it = m_games.begin(); it != m_games.end(); it++)
    {
        if (it->getGameId() == gameId)
        {
            m_games.erase(it);
            return;
        }
    }
}

Game& GameManager::getGameForUser(const LoggedUser& user)
{
    for (auto& game : m_games) 
    {
        if (game.hasPlayer(user)) 
        {
            return game;
        }
    }
    throw std::runtime_error("User not found in any game");
}

/// <summary>
/// Generates a unique random id to game
/// </summary>
/// <returns>Game id</returns>
unsigned int GameManager::generateUniqueGameId()
{
    srand(time(NULL));
    unsigned int newId;
    bool idExists;

    do 
    {
        newId = rand() % 10000 + 1;  // 1-10000
        idExists = false;

        // Check if the ID already exists in the games vector
        for (const auto& game : m_games)
        {
            if (game.getGameId() == newId) 
            {
                idExists = true;
                break;
            }
        }
    } while (idExists);

    return newId;
}
