#include "DatabaseAccess.h"

void DatabaseAccess::InitDb()
{
    std::string msg = "CREATE TABLE USERS(NAME TEXT NOT NULL PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);

    msg = "CREATE TABLE QUESTIONS(QUESTION TEXT NOT NULL PRIMARY KEY, CORRECT TEXT NOT NULL, INCORRECT1 TEXT NOT NULL, INCORRECT2 TEXT NOT NULL, INCORRECT3 TEXT NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);

    msg = "CREATE TABLE STATISTICS(USERNAME TEXT NOT NULL PRIMARY KEY, AVERAGEANSWERTIME REAL NOT NULL, CORRECTANSWERS INTEGER NOT NULL, TOTALANSWERS INTEGER NOT NULL, PLAYEDGAMES INTEGER NOT NULL, PLAYERSCORE INTEGER NOT NULL)";
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
    std::list<Question> questionList;
    std::string msg = "SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + amt;
    sqlite3_exec(db, msg.c_str(), getQuestionData, &questionList, nullptr);

    return questionList;
}

int DatabaseAccess::getQuestionData(void* data, int argc, char** argv, char** azColName) 
{ // question correct incorrect incorrect incorrect
    std::list<Question>* questionList = (std::list<Question>*)data;
    std::vector<std::string> questions;
    for (int i = 1; i <= 4; i++)
    {
        questions.push_back(argv[i]);
    }

    Question q(argv[0], questions, argv[1]);
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
    dataString->append(argv[0] + '|');
    dataString->append(argv[1]);
    return 0;
}


float DatabaseAccess::getPlayerAverageAnswerTime(std::string username)
{
    float answerTime;
    std::string msg = "SELECT AVERAGEANSWERTIME FROM STATISTICS WHERE NAME = '" + username + "'";
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
    std::string msg = "SELECT "+ dataType +" FROM STATISTICS WHERE NAME = '" + username + "'";
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
    std::string msg = "SELECT NAME, MAX(" + type + ") LIMIT 10";
    sqlite3_exec(db, msg.c_str(), highScoreCallback, &value, nullptr);
    return value;
}
