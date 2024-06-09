#include "Question.h"

void Question::shuffleVector()
{

    for (int i = this->m_possibleAnswers.size() - 1; i > 0; --i)
    {
        int j = std::rand() % (i + 1);
        
        std::swap(this->m_possibleAnswers[i], this->m_possibleAnswers[j]);
    }
}
