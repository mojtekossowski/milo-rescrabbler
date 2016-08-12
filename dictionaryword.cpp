#include "dictionaryword.h"

#include <iostream>
#include "exceptions.h"

DictionaryWord::DictionaryWord(const std::string &baseWord)
    : _word (baseWord)
    , _stack (LettersStack(this->_word))
{

}

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

char DictionaryWord::operator-(DictionaryWord &another) const
{
    return this->_stack - another.stack();
}

std::string &DictionaryWord::word()
{
    return this->_word;
}

void DictionaryWord::setWord(const std::string &word)
{
    this->_word = word;
}

unsigned long DictionaryWord::lenght() const
{
    return this->_word.length();
}

LettersStack &DictionaryWord::stack()
{
    return this->_stack;
}

void DictionaryWord::setStack(LettersStack &stack)
{
    this->_stack = stack;
}
