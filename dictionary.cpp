#include "dictionary.h"

Dictionary *Dictionary::dictionarySingleton = nullptr;

Dictionary *Dictionary::getInstance()
{
    if (!dictionarySingleton)
        dictionarySingleton = new Dictionary();

    return dictionarySingleton;
}

void Dictionary::parseDictionary(const std::vector<std::string> &dictionary)
{
    std::for_each(dictionary.begin(), dictionary.end(), [&] (std::string word){
        this->_records.insert(std::pair<int, DictionaryWord> (word.size(), DictionaryWord(word, "")));
    });
}

void Dictionary::clearDictionary()
{
    this->_records.clear();
    this->_baseWord = "";
}

std::string Dictionary::getBaseWord() const
{
    return this->_baseWord;
}

void Dictionary::setBaseWord(const std::string &baseWord)
{
    this->_baseWord = baseWord;
}

Dictionary::Dictionary()
    : _baseWordSize (3)
{

}
