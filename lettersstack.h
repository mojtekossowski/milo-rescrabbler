#ifndef LETTERSSTACK_H
#define LETTERSSTACK_H

#include <QtCore/qglobal.h>
#include <map>

class LettersStack
{
public:
    explicit LettersStack(const std::string &word);

    std::map<char, unsigned int> &stackedLetters();
    void setStackedLetters(std::map<char, unsigned int> &stackedLetters);

    bool contains (LettersStack &another);
    char operator-(LettersStack &another) const;

private:
    std::map<char, unsigned int> _stackedLetters;
};

#endif // LETTERSSTACK_H
