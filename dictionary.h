#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtCore/qglobal.h>
#include <map>
#include <list>

#include "dictionaryword.h"

class Dictionary
{
public:
    static Dictionary *getInstance();

    void parseDictionary(const std::vector<std::string> &dictionary);
    void clearDictionary();

    void run();

    DictionaryWord &baseWord();
    void setBaseWord(const std::string &word);

private:
    Dictionary();
    void findAnnagrams(const DictionaryWord &word, int depth) noexcept (false);

    static Dictionary *dictionarySingleton;
    std::multimap<int, DictionaryWord> _records;
    DictionaryWord _baseWord;
    std::list<std::pair<char, DictionaryWord*>> _result;
    int _maxWordSize;
};

#endif // DICTIONARY_H
