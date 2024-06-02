#include "DatabaseAccess.h"

void DatabaseAccess::InitDb()
{
    std::string msg = "CREATE TABLE USERS(NAME TEXT NOT NULL PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);

    msg = "CREATE TABLE QUESTIONS(QUESTION TEXT NOT NULL PRIMARY KEY, CORRECT TEXT NOT NULL, INCORRECT1 TEXT NOT NULL, INCORRECT2 TEXT NOT NULL, INCORRECT3 TEXT NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);

    msg = "CREATE TABLE STATISTICS(USERNAME TEXT NOT NULL PRIMARY KEY, AVERAGEANSWERTIME REAL NOT NULL, CORRECTANSWERS INTEGER NOT NULL, TOTALANSWERS INTEGER NOT NULL, PLAYEDGAMES INTEGER NOT NULL, PLAYERSCORE INTEGER NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);
}

bool DatabaseAccess::doesUserExist(std::string name)
{
    bool Exists = false;
    std::string msg = "SELECT * FROM USERS WHERE NAME = '" + name + "'";
    sqlite3_exec(db, msg.c_str(), check, &Exists, nullptr);

    return Exists;
}

void DatabaseAccess::addUser(std::string name, std::string pass, std::string email)
{
    std::string msg = "INSERT INTO USERS(NAME, PASSWORD, EMAIL) VALUES('" + name + "', '" + pass + "', '" + email + "'"")";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);
}

bool DatabaseAccess::isPassCorrect(std::string name, std::string pass)
{
    std::string password;
    std::string msg = "SELECT PASSWORD FROM USERS WHERE NAME = '" + name + "'";
    sqlite3_exec(db, msg.c_str(), checkPass, &password, nullptr);
    return (pass == password);
}



std::map<std::string, std::string> DatabaseAccess::getAccountData(std::string name)
{
    std::string msg = "SELECT * FROM USERS WHERE NAME = '" + name + "'";
    std::map<std::string, std::string> data;
    sqlite3_exec(db, msg.c_str(), getData, &data, nullptr);
    return data;
}

int DatabaseAccess::check(void* data, int argc, char** argv, char** azColName)
{
    bool* Exists = (bool*)data;
    *Exists = argc;
    return 0;
}

int DatabaseAccess::checkPass(void* data, int argc, char** argv, char** azColName)
{
    std::string* ok = (std::string*)data;
    *ok = argv[0];
    return 0;
}

int DatabaseAccess::getData(void* data, int argc, char** argv, char** azColName)
{
    std::map<std::string, std::string>* map = (std::map<std::string, std::string>*)data;
    (*map)["password"] = argv[1];
    (*map)["email"] = argv[2];
    return 0;
}

std::list<Question> DatabaseAccess::getQuestions(int amt)
{
    std::list<Question>* questionList = new std::list<Question>();
    std::string msg = "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + std::to_string(amt);
    std::cout << msg;
    sqlite3_exec(db, msg.c_str(), getQuestionData, questionList, nullptr);

    return *questionList;
}

int DatabaseAccess::getQuestionData(void* data, int argc, char** argv, char** azColName) 
{ // question correct incorrect incorrect incorrect
    std::list<Question>* questionList = (std::list<Question>*)data; //q 1 2 3 4
    std::vector<std::string> questions;
    for (int i = 1; i <= 4; i++)
    {
        questions.push_back(argv[i]);
    }

    Question q(argv[0], questions);
    questionList->push_back(q);
    return 0;
}

int DatabaseAccess::intStatisticCallback(void* data, int argc, char** argv, char** azColName)
{
    *(int*)data = std::atoi(argv[0]);
    return 0;
}

int DatabaseAccess::floatStatisticCallback(void* data, int argc, char** argv, char** azColName)
{
    *(float*)data = std::atof(argv[0]);
    return 0;
}

int DatabaseAccess::highScoreCallback(void* data, int argc, char** argv, char** azColName)
{
    
    std::string* dataString = (std::string*)data;
    dataString->append(argv[0]); //name|score,name2|score
    dataString->append("|");
    dataString->append(argv[1]);
    dataString->append(",");

    std::cout << std::endl << dataString << std::endl;
    return 0;
}

int DatabaseAccess::submitGameStatistics(const std::string& username, const GameData& gameData)
{
    // Prepare SQL statements
    std::string selectQuery = "SELECT * FROM STATISTICS WHERE USERNAME = ?;";
    std::string insertQuery = "INSERT INTO STATISTICS (USERNAME, AVERAGEANSWERTIME, CORRECTANSWERS, TOTALANSWERS, PLAYEDGAMES, PLAYERSCORE) VALUES (?, ?, ?, ?, ?, ?);";
    std::string updateQuery = "UPDATE STATISTICS SET AVERAGEANSWERTIME = ?, CORRECTANSWERS = ?, TOTALANSWERS = ?, PLAYEDGAMES = ?, PLAYERSCORE = ? WHERE USERNAME = ?;";

    sqlite3_stmt* stmt;
    int rc;

    // Check if the user already exists
    rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare select statement: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Bind the username to the select statement
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) 
    {
        // User exists, update the row
        double currentAvgAnswerTime = sqlite3_column_double(stmt, 1);
        unsigned int currentCorrectAnswers = sqlite3_column_int(stmt, 2);
        unsigned int currentTotalAnswers = sqlite3_column_int(stmt, 3);
        unsigned int currentPlayedGames = sqlite3_column_int(stmt, 4);
        unsigned int currentPlayerScore = sqlite3_column_int(stmt, 5);

        unsigned int totalAnswers = currentTotalAnswers + gameData.correctAnswerCount + gameData.wrongAnswerCount;
        double newAvgAnswerTime = (gameData.averageAnswerTime * (gameData.correctAnswerCount + gameData.wrongAnswerCount) + currentAvgAnswerTime * currentTotalAnswers) / totalAnswers;
        unsigned int newCorrectAnswers = currentCorrectAnswers + gameData.correctAnswerCount;
        unsigned int newTotalAnswers = totalAnswers;
        unsigned int newPlayedGames = currentPlayedGames + 1;
        unsigned int newPlayerScore = currentPlayerScore + gameData.score;

        // Finalize the select statement
        sqlite3_finalize(stmt);

        // Prepare the update statement
        rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare update statement: " << sqlite3_errmsg(db) << std::endl;
            return 1;
        }

        // Bind the values to the update statement
        sqlite3_bind_double(stmt, 1, newAvgAnswerTime);
        sqlite3_bind_int(stmt, 2, newCorrectAnswers);
        sqlite3_bind_int(stmt, 3, newTotalAnswers);
        sqlite3_bind_int(stmt, 4, newPlayedGames);
        sqlite3_bind_int(stmt, 5, newPlayerScore);
        sqlite3_bind_text(stmt, 6, username.c_str(), -1, SQLITE_STATIC);

        // Execute the update statement
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) 
        {
            std::cerr << "Failed to update row: " << sqlite3_errmsg(db) << std::endl;
        }

    }
    else if (rc == SQLITE_DONE) 
    {
        // User does not exist, insert a new row
        sqlite3_finalize(stmt);

        // Prepare the insert statement
        rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK) 
        {
            std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
            return 1;
        }

        // Bind the values to the insert statement
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 2, gameData.averageAnswerTime);
        sqlite3_bind_int(stmt, 3, gameData.correctAnswerCount);
        sqlite3_bind_int(stmt, 4, gameData.correctAnswerCount + gameData.wrongAnswerCount);
        sqlite3_bind_int(stmt, 5, 1);
        sqlite3_bind_int(stmt, 6, gameData.score);

        // Execute the insert statement
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            std::cerr << "Failed to insert row: " << sqlite3_errmsg(db) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to step through select statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return 0;
}

void DatabaseAccess::addQuestion(std::string question, std::vector<std::string> answers)
{
    //(QUESTION TEXT NOT NULL PRIMARY KEY, CORRECT TEXT NOT NULL, INCORRECT1 TEXT NOT NULL, INCORRECT2 TEXT NOT NULL, INCORRECT3 TEXT NOT NULL)
    std::string msg = "INSERT INTO QUESTIONS(QUESTION, CORRECT,INCORRECT1,INCORRECT2,INCORRECT3) VALUES ( '" + question + "', '" + answers[0] + "', '" + answers[1] + "', '" + answers[2] + "', '" + answers[3] + "')";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);
}


float DatabaseAccess::getPlayerAverageAnswerTime(std::string username)
{
    float answerTime;
    std::string msg = "SELECT AVERAGEANSWERTIME FROM STATISTICS WHERE USERNAME = '" + username + "'";
    sqlite3_exec(db, msg.c_str(), floatStatisticCallback, &answerTime, nullptr);
    return answerTime;
}

int DatabaseAccess::getNumOfCorrectAnswers(std::string username)
{
    return getIntScore(username, "CORRECTANSWERS");
}

int DatabaseAccess::getNumOfTotalAnswers(std::string username)
{
    return getIntScore(username, "TOTALANSWERS");
}

int DatabaseAccess::getNumOfPlayerGames(std::string username)
{
    return getIntScore(username, "PLAYEDGAMES");
}

int DatabaseAccess::getPlayerScore(std::string username)
{
    return getIntScore(username, "PLAYERSCORE");
}

int DatabaseAccess::getIntScore(std::string username, std::string dataType)
{
    int answer;
    std::string msg = "SELECT "+ dataType +" FROM STATISTICS WHERE USERNAME = '" + username + "'";
    sqlite3_exec(db, msg.c_str(), intStatisticCallback, &answer, nullptr);
    return answer;
}

// TO-DO
// VERY IMPORTANT!!
// CHANGE to get the 10 BEST SCORES
// in the following FORMAT:
// username1|score, username2|score, username3|score, ..., username10|score
std::vector<std::string> DatabaseAccess::getHighScores()
{
    std::vector<std::string> highScores;
    //order is going to be Correct answers -> Total answers -> Played games -> Player score -> Average answer time
    highScores.push_back(getMaxStat("PLAYERSCORE"));

    return highScores;
}

std::string DatabaseAccess::getMaxStat(std::string type)
{
    std::string value;
    std::string msg = "SELECT USERNAME, MAX("+ type +") AS MAXSCORE FROM STATISTICS GROUP BY USERNAME ORDER BY MAXSCORE DESC LIMIT 10";
    sqlite3_exec(db, msg.c_str(), highScoreCallback, &value, nullptr);
    return value;
}
