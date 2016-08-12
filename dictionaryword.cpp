#include "dictionaryword.h"

#include <iostream>
#include "exceptions.h"

//!
//! \brief DictionaryWord::DictionaryWord ctor of base word
//! \param baseWord base word
//!
DictionaryWord::DictionaryWord(const std::string &baseWord)
    : _word (baseWord)
    , _stack (LettersStack(this->_word))
{

}

//!
//! \brief DictionaryWord::DictionaryWord ctor depending on base word
//! throws an anagram_not_matched if word does not contain base
//! \param word current parsing word
//! \param baseWord base word
//!
DictionaryWord::DictionaryWord(const std::string &word,
                               DictionaryWord &baseWord) noexcept(false)
    : _word (std::move(word))
    , _stack (LettersStack(this->_word))
{
    if (!this->_stack.contains(baseWord.stack()))
    {
        throw anagram_not_matched();
    }
}

//!
//! \brief DictionaryWord::operator - (uses stack difference)
//! \param another another DictionaryWord
//! \return letter diff
//!
char DictionaryWord::operator-(DictionaryWord &another) const
{
    return this->_stack - another.stack();
}

//!
//! \brief DictionaryWord::word
//! \return word
//!
std::string &DictionaryWord::word()
{
    return this->_word;
}

//!
//! \brief DictionaryWord::lenght
//! \return words length
//!
unsigned long DictionaryWord::lenght() const
{
    return this->_word.length();
}

//!
//! \brief DictionaryWord::stack
//! \return letters stack
//!
LettersStack &DictionaryWord::stack()
{
    return this->_stack;
}
