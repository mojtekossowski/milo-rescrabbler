#include "lettersstack.h"
#include <iostream>

//!
//! \brief LettersStack::LettersStack
//! \details Constructor - build LettersStack from provided >>word<<
//! \param word Word to parse
//!
LettersStack::LettersStack(const std::string &word)
{
    // Count all letter occurances and push them to the map
    std::for_each(word.begin(),
                  word.end(),
                  [&](const char &l)
    {
        // Simple&Sexy - map's components are set to 0 by default
        this->_stackedLetters[l]++;
    });
}

//!
//! \brief LettersStack::stackedLetters
//! \details Reference to internal, raw map (letter:occurance)
//! \return Raw stack map
//!
std::map<char, unsigned int> &LettersStack::stackedLetters()
{
    return this->_stackedLetters;
}

//!
//! \brief LettersStack::contains
//! \details Checks if 'this' LetterStack contains >>another<< LetterStack.
//! This method checks all occurances of >>another<< LetterStack onto this.
//! \param another Another LetterStack
//! \return match
//!
bool LettersStack::contains(LettersStack &another)
{
    for (auto item = another.stackedLetters().begin();
         item != another.stackedLetters().end();
         item++)
    {
        // If this map has no key (letter) from 'another' stack - fail
        if (!(this->_stackedLetters[(*item).first]))
            return false;

        // If occurance count of 'another'-s letter is higher - fail
        if ((this->_stackedLetters[(*item).first]) < (*item).second)
            return false;
    }

    // 'this' contains 'another'
    return true;
}

//!
//! \brief LettersStack::operator -
//! Overloaded substitution operator
//! \details Method maniputales through letter occurance map
//! and removes counts of whole >>another<< LettersStack on this.
//! if transition is not possible, an empty character is returned
//! \param another Another LetterStack
//! \return Diff letter
//!
char LettersStack::operator-(LettersStack &another) const
{
    // Assign empty char as default
    char letter = '\0';
    // Copy local stack (higher rank)
    std::map<char, unsigned int> tempStack = this->_stackedLetters;

    // Iterate through stack
    for (auto item = another.stackedLetters().cbegin();
         item != another.stackedLetters().cend();
         item++)
    {
        // If local stack does not contain letter of 'another' stack - fail
        if (!(tempStack[(*item).first]))
            return letter;

        // If number of occurances doesnt cover the 'another' stack - fail
        if ((tempStack[(*item).first]) < (*item).second)
            return letter;

        // Substrack occurances of 'another'-s LetterStack on this
        tempStack[(*item).first] -= (*item).second;
    }

    // Iterate once again on temporary stack
    // to obtain the differential letter
    for (auto item = tempStack.begin();
         item != tempStack.end();
         item++)
    {
        // Letter:occurance, return the key (letter)
        if ((*item).second > 0)
            return (*item).first;
    }

    // If nothing was found return empty character
    return letter;
}
