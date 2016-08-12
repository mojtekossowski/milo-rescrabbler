#ifndef DICTIONARYWORD_H
#define DICTIONARYWORD_H

#include <QtCore/qglobal.h>
#include <map>

#include "lettersstack.h"

class DictionaryWord
{
public:
    explicit DictionaryWord (const std::string &baseWord);

    DictionaryWord(const std::string &word,
                   DictionaryWord &baseWord) noexcept (false);

    char operator-(DictionaryWord &another) const;

    std::string &word();
    void setWord(const std::string &word);

    unsigned long lenght() const;

    LettersStack &stack();
    void setStack(LettersStack &stack);

private:
    std::string _word;
    LettersStack _stack;
};

#endif // DICTIONARYWORD_H
