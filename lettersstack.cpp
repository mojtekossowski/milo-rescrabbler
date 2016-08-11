#include "lettersstack.h"
#include <iostream>

LettersStack::LettersStack(const std::string &word)
{
    std::for_each(word.begin(),
                  word.end(),
                  [&](const char &l)
    {
        this->_stackedLetters[l]++;
    });
}

std::map<char, unsigned int> &LettersStack::stackedLetters()
{
    return this->_stackedLetters;
}

void LettersStack::setStackedLetters(std::map<char, unsigned int> &stackedLetters)
{
    this->_stackedLetters = std::move(stackedLetters);
}

bool LettersStack::contains(LettersStack &another)
{
    for (auto item = another.stackedLetters().begin();
         item != another.stackedLetters().end();
         item++)
    {
        if (!(this->_stackedLetters[(*item).first]))
            return false;

        if ((this->_stackedLetters[(*item).first]) < (*item).second)
            return false;
    }

    return true;
}

char LettersStack::operator-(LettersStack &another) const
{
    char letter = '\0';
    std::map<char, unsigned int> tempStack = this->_stackedLetters;

    if (this->_stackedLetters.size() - another.stackedLetters().size() != 1)
        return letter;

    for (auto item = another.stackedLetters().cbegin();
         item != another.stackedLetters().cend();
         item++)
    {
        if (!(tempStack[(*item).first]))
            return letter;

        if ((tempStack[(*item).first]) < (*item).second)
            return letter;

        tempStack[(*item).first] -= (*item).second;
    }

    std::cout << std::endl;
    for (auto item = tempStack.begin();
         item != tempStack.end();
         item++)
    {
        if ((*item).second > 0)
            return (*item).first;
    }

    return letter;
}
