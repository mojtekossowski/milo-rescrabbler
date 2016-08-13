#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtCore/qglobal.h>
#include <map>
#include <list>

#include "dictionaryword.h"

//!
//! \brief The Dictionary class
//! The main Dictionary class - performs algorithm, loads
//! dictionary and stores the data.
//! \details The dictionary multimap
//! (std::multimap<unsigned long, DictionaryWord> _records)
//! contains ascending, sorted and categorized by word size
//! dictionary word.
//!
//! Follow the manual in such order:
//! @see parseDictionary
//! @see addWordToDictionary
//! @see run
//! @see findAnnagrams
//!
class Dictionary
{
public:
    static Dictionary *getInstance();

    void parseDictionary(const std::vector<std::string> &dictionary);
    void parseDictionary(const std::string &filepath);
    void clearDictionary();

    void run();
    unsigned long depth() const;

    DictionaryWord &baseWord();
    void setBaseWord(const std::string &word);

private:
    Dictionary(); // Yeah, private ctor. I am Singleton, man!
    void findAnnagrams(DictionaryWord *word, unsigned long depth) noexcept (false);
    void addWordToDictionary(const std::string &word);

    // Pointer to global instance
    static Dictionary *dictionarySingleton;
    // All records - Length:DictionaryWord
    std::multimap<unsigned long, DictionaryWord> _records;
    // Base lookup word
    DictionaryWord _baseWord;
    // The winning result - AddedLetter:DictionaryWord
    std::list<std::pair<char, DictionaryWord*> > _result;
    // Max word size in dictionary - needed at beginning
    unsigned long _maxWordSize;
};

#endif // DICTIONARY_H
