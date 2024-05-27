#include "Question.h"

void Question::shuffleVector()
{
    std::srand(std::time(0));

    for (size_t i = this->m_possibleAnswers.size() - 1; i > 0; --i) {
        size_t j = std::rand() % (i + 1);
        
        std::swap(this->m_possibleAnswers[i], this->m_possibleAnswers[j]);
    }
}
