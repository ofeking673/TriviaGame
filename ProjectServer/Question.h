#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define NO_MORE_QUESTIONS_LEFT 0

class Question
{
public:
    // TO-DO check DB after the change of Question constructor

    Question() : m_question(""), m_correctAnswerId(NO_MORE_QUESTIONS_LEFT) {};

    Question(std::string question, std::vector<std::string> answers)
        : m_question(question), m_possibleAnswers(answers), m_correctAnswerId(1/*Will be changed inside*/)
    {
        if (!answers.empty())
        {
            // Correct answer is always the first one in the provided vector
            std::string correctAnswer = answers[0];

            // Shuffle the 
            shuffleVector();

            // Find the id of the correct answer in the shuffled list
            auto it = std::find(m_possibleAnswers.begin(), m_possibleAnswers.end(), correctAnswer);
            if (it != m_possibleAnswers.end())
            {
                m_correctAnswerId = std::distance(m_possibleAnswers.begin(), it);
            }
        }
        else
        {
            m_correctAnswerId = NO_MORE_QUESTIONS_LEFT;
        }
    }

	~Question() {};

    void shuffleVector();
	std::string getQuestion() const { return m_question; };
	std::vector<std::string> getPossibleAnswers() const { return m_possibleAnswers; };
	unsigned int getCorrectAnswerId() const { return m_correctAnswerId; };
    bool operator==(const Question& other) const { return (m_question == other.m_question); };
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	unsigned int m_correctAnswerId;
};