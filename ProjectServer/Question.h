#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Question
{
public:

	Question(std::string question, std::vector<std::string> answers)
        : m_question(question), m_possibleAnswers(answers) 
    {
        // Correct answer is always the first one in the provided vector
        std::string correctAnswer = answers[0];

        // Shuffle the answers
        std::srand(unsigned(std::time(0)));
        std::random_shuffle(m_possibleAnswers.begin(), m_possibleAnswers.end());

        // Find the id of the correct answer in the shuffled list
        auto it = std::find(m_possibleAnswers.begin(), m_possibleAnswers.end(), correctAnswer);
        if (it != m_possibleAnswers.end()) 
        {
            m_correctAnswerId = std::distance(m_possibleAnswers.begin(), it);
        }
    }

	~Question() {};

	std::string getQuestion() const { return m_question; };
	std::vector<std::string> getPossibleAnswers() const { return m_possibleAnswers; };
	unsigned int getCorrectAnswerId() const { return m_correctAnswerId; };
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	unsigned int m_correctAnswerId;
};