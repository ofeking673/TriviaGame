#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question(std::string question, std::vector<std::string> answers, std::string correctAnswer) : m_question(question), m_possibleAnswers(answers), correctAnswer(correctAnswer) {};
	~Question() {};

	std::string getQuestion() { return m_question; };
	std::vector<std::string> getPossibleAnswers() { return m_possibleAnswers; };
	std::string getCorrectAnswer() { return correctAnswer; };
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	std::string correctAnswer;
};