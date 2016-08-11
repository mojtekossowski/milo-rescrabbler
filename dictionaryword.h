#ifndef DICTIONARYWORD_H
#define DICTIONARYWORD_H

#include <QtCore/qglobal.h>
#include <map>

class DictionaryWord
{
public:
explicit DictionaryWord(std::string &word,
                        const std::string &baseWord);

    char operator-(const DictionaryWord &another);

private:
    std::string _word;
    std::map<char, unsigned int> _stackedLetters;
};

#endif // DICTIONARYWORD_H
