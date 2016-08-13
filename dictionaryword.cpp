#include "dictionaryword.h"

#include <iostream>
#include "exceptions.h"

//!
//! \brief DictionaryWord::DictionaryWord
//! \details Constructor of DictionaryWord for >>baseWord<<
//! automaticaly generates LetterStack.
//! \param baseWord base word
//!
DictionaryWord::DictionaryWord(const std::string &baseWord)
    : _word (baseWord)
    , _stack (LettersStack(this->_word))
{

}

//!
//! \brief DictionaryWord::operator -
//! \details Returns character difference between two words stored in dictionary.
//! The difference mechanism works always for size(this) - size(another) = 1.
//! @see LetterStack::operator-() for more details.
//! \param another Another DictionaryWord
//! \return Letter diff
//!
char DictionaryWord::operator-(DictionaryWord &another) const
{
    return this->_stack - another.stack();
}

//!
//! \brief DictionaryWord::contains
//! Function returns matching criteria
//! \param another
//! \return
//!
bool DictionaryWord::contains(DictionaryWord &another)
{
    return this->_stack.contains(another.stack());
}

//!
//! \brief DictionaryWord::word
//! \return Printable word (from dictionary)
//!
std::string &DictionaryWord::word()
{
    return this->_word;
}

//!
//! \brief DictionaryWord::lenght
//! \return Word's length (from dictionary)
//!
unsigned long DictionaryWord::lenght() const
{
    return this->_word.length();
}

//!
//! \brief DictionaryWord::stack
//! \return Letters stack
//!
LettersStack &DictionaryWord::stack()
{
    return this->_stack;
}
