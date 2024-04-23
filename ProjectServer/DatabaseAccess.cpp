#include "DatabaseAccess.h"

void DatabaseAccess::InitDb()
{
    std::string msg = "CREATE TABLE USERS(NAME TEXT NOT NULL PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);

    msg = "CREATE TABLE QUESTIONS(QUESTION TEXT NOT NULL PRIMARY KEY, CORRECT TEXT NOT NULL, INCORRECT1 TEXT NOT NULL, INCORRECT2 TEXT NOT NULL, INCORRECT3 TEXT NOT NULL)";
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
    std::string msg = "SELECT PASS FROM USERS WHERE NAME = '" + name + "'";
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



float DatabaseAccess::getPlayerAverageAnswerTime(std::string username)
{
    return 0.0f;
}

int DatabaseAccess::getNumOfCorrectAnswers(std::string username)
{
    return 0;
}

int DatabaseAccess::getNumOfTotalAnswers(std::string username)
{
    return 0;
}

int DatabaseAccess::getNumOfPlayerGames(std::string username)
{
    return 0;
}

int DatabaseAccess::getPlayerScore(std::string username)
{
    return 0;
}

std::vector<std::string> DatabaseAccess::getHighScores()
{
    return std::vector<std::string>();
}
