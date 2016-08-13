#ifndef DICTIONARYWORD_H
#define DICTIONARYWORD_H

#include <QtCore/qglobal.h>
#include <map>

#include "lettersstack.h"

//!
//! \brief The DictionaryWord class
//! Represent single dictionary word with:
//! * readable word
//! * stack of letter's occurance
//!
class DictionaryWord
{
public:
    explicit DictionaryWord (const std::string &baseWord);

    DictionaryWord(const std::string &word,
                   DictionaryWord &baseWord) noexcept (false);

    char operator-(DictionaryWord &another) const;

    std::string &word();
    unsigned long lenght() const;
    LettersStack &stack();

private:
    // Printable word
    std::string _word;
    // Letters stack
    LettersStack _stack;
};

#endif // DICTIONARYWORD_H
