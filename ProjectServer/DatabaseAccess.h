#pragma once
#include <iostream>
#include "sqlite3.h"
#include "IDatabase.h"
#include <io.h>

class DatabaseAccess : public IDatabase
{
public:

	// Access the single instance
	static DatabaseAccess& getInstance();

	// Delete copy constructors
	DatabaseAccess(const DatabaseAccess&) = delete;
	DatabaseAccess& operator=(const DatabaseAccess&) = delete;





	virtual void open(std::string fileName) override
	{
		int test = _access(fileName.c_str(), 0);
		sqlite3_open(fileName.c_str(), &db);

		if (test == -1)
		{
			InitDb();
		}

		//"int variable;", "variable int;", "int = variable;", "variable = int;"
		//	void addQuestion(std::string question, std::vector<std::string> answers);
		/*std::vector<std::string> answers = {"Hello", "hello2", "hello3", "hello4"};
		addQuestion("Q1", answers);*/
	};

	virtual void close() override {
		sqlite3_close(db);
		db = nullptr;
		delete this;
	};

	virtual void InitDb() override;
	
	virtual bool doesUserExist(std::string name) override;
	virtual void addUser(std::string name, std::string pass, std::string email) override;
	virtual bool isPassCorrect(std::string name, std::string pass) override;

	virtual std::map<std::string, std::string> getAccountData(std::string name) override;

	static int check(void* data, int argc, char** argv, char** azColName);
	static int checkPass(void* data, int argc, char** argv, char** azColName);
	static int getData(void* data, int argc, char** argv, char** azColName);

	// Room & statistics related
	virtual std::list<Question> getQuestions(int amt /*?*/);
	virtual float getPlayerAverageAnswerTime(std::string username);
	virtual int getNumOfCorrectAnswers(std::string username);
	virtual int getNumOfTotalAnswers(std::string username);
	virtual int getNumOfPlayerGames(std::string username);
	virtual int getPlayerScore(std::string username);
	int getIntScore(std::string username, std::string dataType);
	// PLEASE RETURN IN FOLLOWING FORMAT:
	// username1 | score, username2 | score, ... 
	virtual std::vector<std::string> getHighScores();
	std::string getMaxStat(std::string type);
	//Room & Statistics related callbacks
	static int getQuestionData(void* data, int argc, char** argv, char** azColName);
	static int intStatisticCallback(void* data, int argc, char** argv, char** azColName);
	static int floatStatisticCallback(void* data, int argc, char** argv, char** azColName);

	static int highScoreCallback(void* data, int argc, char** argv, char** azColName);



	// Game related
	virtual int submitGameStatistics(const std::string& username, const GameData& gameData);
	virtual void addQuestion(std::string question, std::vector<std::string> answers) override;
private:


	// Private ctor
	DatabaseAccess() 
	{
		open(FILENAME);
	}

	// Private dtor
	~DatabaseAccess() 
	{
		close();
	}

	// Static method to initialize the singleton instance
	static void initSingleton();

	// Pointer to the single instance
	static DatabaseAccess* instance;

	// Flag to ensure the instance is only created once
	static std::once_flag initInstanceFlag;



	sqlite3* db;
};
