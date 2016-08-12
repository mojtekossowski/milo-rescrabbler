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
    void parseDictionary(const std::string &filepath);
    void clearDictionary();

    void run();

    DictionaryWord &baseWord();
    void setBaseWord(const std::string &word);

private:
    Dictionary();
    void findAnnagrams(DictionaryWord *word, unsigned long depth) noexcept (false);
    void addWordToDictionary(const std::string &word);

    static Dictionary *dictionarySingleton;
    std::multimap<unsigned long, DictionaryWord> _records;
    DictionaryWord _baseWord;
    std::list<std::pair<char, DictionaryWord*> > _result;
    unsigned long _maxWordSize;
};

#endif // DICTIONARY_H
