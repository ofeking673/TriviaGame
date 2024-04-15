#include "DatabaseAccess.h"

void DatabaseAccess::InitDb()
{
    std::string msg = "CREATE TABLE USERS(NAME TEXT NOT NULL PRIMARY KEY, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL)";
    sqlite3_exec(db, msg.c_str(), nullptr, nullptr, nullptr);
}

bool DatabaseAccess::doesUserExist(std::string name)
{
    bool Exists = false;
    std::string msg = "SELECT * FROM USERS WHERE NAME = '" + name + "'";
    sqlite3_exec(db, msg.c_str(), check, &Exists, nullptr);

    return Exists;
}

int check(void* data, int argc, char** argv, char** azColName)
{
    bool* Exists = (bool*)data;
    *Exists = argc;
    return 0;
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

int checkPass(void* data, int argc, char** argv, char** azColName)
{
    std::string* ok = (std::string*)data;
    *ok = argv[0];
}

std::map<std::string, std::string> DatabaseAccess::getAccountData(std::string name)
{
    std::string msg = "SELECT * FROM USERS WHERE NAME = '" + name + "'";
    std::map<std::string, std::string> data;
    sqlite3_exec(db, msg.c_str(), getData, &data, nullptr);
    return data;
}

int getData(void* data, int argc, char** argv, char** azColName)
{
    std::map<std::string, std::string>* map = (std::map<std::string, std::string>*)data;
    map["password"] = argv[1];
    map["email"] = argv[2];
}