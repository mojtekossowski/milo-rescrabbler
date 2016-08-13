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
//! \brief DictionaryWord::DictionaryWord
//! \details Constructor of DictionaryWord for >>word<<,
//! regarding to >>baseWord<<. Automaticaly generates LettersStack.
//! Throws an 'anagram_not_matched' exception if
//! >>word<< LettersStack does not contain >>baseWord<< LettersStack.
//! \param word current parsing word
//! \param baseWord base word
//!
DictionaryWord::DictionaryWord(const std::string &word,
                               DictionaryWord &baseWord) noexcept(false)
    : _word (std::move(word))
    , _stack (LettersStack(this->_word))
{
    // If currently created word doesn't match the baseWord
    if (!this->_stack.contains(baseWord.stack()))
    {
        // Throw an exception (revert object creation) - handled upwards.
        throw anagram_not_matched();
    }
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
