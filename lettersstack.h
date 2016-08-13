#ifndef LETTERSSTACK_H
#define LETTERSSTACK_H

#include <QtCore/qglobal.h>
#include <map>

//!
//! \brief The LettersStack class
//! Represents the letter stack with several methods:
//! * substraction of neariest words
//!
class LettersStack
{
public:
    explicit LettersStack(const std::string &word);

    std::map<char, unsigned int> &stackedLetters();

    bool contains (LettersStack &another);
    char operator-(LettersStack &another) const;

private:
    // Map which contains occurance of all letters
    std::map<char, unsigned int> _stackedLetters;
};

#endif // LETTERSSTACK_H
