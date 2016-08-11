#include "dictionaryword.h"

#include <iostream>

DictionaryWord::DictionaryWord(std::string &word, const std::string &baseWord)
    : _word (word)
{
    std::for_each(word.begin(),
                  word.end(),
                  [&](const char &l)
    {
        this->_stackedLetters[l]++;
    });

    std::cout << word << std::endl;

    std::for_each(this->_stackedLetters.begin(),
                  this->_stackedLetters.end(),
                  [](const std::pair<char, int> &letter)
    {
        std::cout << "Letter: " << letter.first
                  << ", Count: " << letter.second << std::endl;
    });

    std::cout << std::endl;
}
