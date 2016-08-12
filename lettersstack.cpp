#include "lettersstack.h"
#include <iostream>

//!
//! \brief LettersStack::LettersStack ctor - build Letters stack from word
//! \param word word from text file / default settings
//!
LettersStack::LettersStack(const std::string &word)
{
    // count all letters and push them to the map
    std::for_each(word.begin(),
                  word.end(),
                  [&](const char &l)
    {
        // simple - map's components are set to 0 by default
        // if there are no present elements.
        this->_stackedLetters[l]++;
    });
}

//!
//! \brief LettersStack::stackedLetters reference to map
//! \return stack map
//!
std::map<char, unsigned int> &LettersStack::stackedLetters()
{
    return this->_stackedLetters;
}

//!
//! \brief LettersStack::contains checks if 'this' contain 'another' LetterStack
//! \param another another LetterStack
//! \return match
//!
bool LettersStack::contains(LettersStack &another)
{
    for (auto item = another.stackedLetters().begin();
         item != another.stackedLetters().end();
         item++)
    {
        // if this map has no key from another stack
        if (!(this->_stackedLetters[(*item).first]))
            return false;

        // if occurance from another is higher
        if ((this->_stackedLetters[(*item).first]) < (*item).second)
            return false;
    }

    // 'this' contains 'another'
    return true;
}

//!
//! \brief LettersStack::operator - overloaded sub operator to obtain letter addition
//! \details method maniputales through map of occurance and removes counts.
//! if transition is not possible, an empty character is returned
//! \param another another LetterStack
//! \return letter diff
//!
char LettersStack::operator-(LettersStack &another) const
{
    // assign empty char as default
    char letter = '\0';
    // copy local stack (higher rank)
    std::map<char, unsigned int> tempStack = this->_stackedLetters;

    // if difference is higher than one - no transition
    if (this->_stackedLetters.size() - another.stackedLetters().size() != 1)
        return letter;

    // iterate through stack
    for (auto item = another.stackedLetters().cbegin();
         item != another.stackedLetters().cend();
         item++)
    {
        // if local stack does not contain letter of 'another' stack
        if (!(tempStack[(*item).first]))
            return letter;

        // if number of occurances doesnt cover the another stack
        if ((tempStack[(*item).first]) < (*item).second)
            return letter;

        // diff
        tempStack[(*item).first] -= (*item).second;
    }

    // iterate once again on temp stack to obtain the letter
    for (auto item = tempStack.begin();
         item != tempStack.end();
         item++)
    {
        // letter:occurance, return the index
        if ((*item).second > 0)
            return (*item).first;
    }

    // if nothing found return \0
    return letter;
}
