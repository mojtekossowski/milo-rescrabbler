#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtCore/qglobal.h>
#include <map>

#include "dictionaryword.h"

class Dictionary
{
public:
    static Dictionary *getInstance();

    void parseDictionary (const std::vector<std::string> &dictionary);

    void clearDictionary();

    std::string getBaseWord() const;
    void setBaseWord(const std::string &baseWord);

private:
    Dictionary();
    static Dictionary *dictionarySingleton;
    std::multimap<int, DictionaryWord> _records;
    std::string _baseWord;
    unsigned int _baseWordSize;
};

#endif // DICTIONARY_H
