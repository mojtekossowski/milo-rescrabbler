#include "dictionary.h"
#include <stdexcept>
#include <iostream>

Dictionary *Dictionary::dictionarySingleton = nullptr;

Dictionary *Dictionary::getInstance()
{
    if (!dictionarySingleton)
        dictionarySingleton = new Dictionary();

    return dictionarySingleton;
}

void Dictionary::parseDictionary(const std::vector<std::string> &dictionary)
{
    this->_records.insert(std::pair<int, DictionaryWord> (this->_baseWord.lenght(), this->_baseWord));

    std::for_each(dictionary.begin(),
                  dictionary.end(),
                  [&] (std::string word)
    {
        try
        {
            if (word.length() <= this->_baseWord.word().length())
                return;

            auto record = DictionaryWord(word, this->_baseWord);
            this->_records.insert(std::pair<int, DictionaryWord> (word.size(), std::move(record)));
            this->_maxWordSize = std::max(this->_maxWordSize, static_cast<int>(word.size()));
        }
        catch (...)
        {
            // Gotta catch'em all ;D
        }
    });
}

void Dictionary::clearDictionary()
{
    this->_records.clear();
}

void Dictionary::run()
{
    try
    {
        for (int i = this->_maxWordSize; i > this->_baseWord.lenght(); --i)
        {
            this->_result.clear();

            auto lastItem = this->_records.equal_range(i);

            for (auto it = lastItem.first;
                 it != lastItem.second;
                 it ++)
            {
                auto rWord = ((*it).second);
                this->_result.push_back(std::pair<char, DictionaryWord*> ('\0', &rWord));
                this->findAnnagrams(rWord, rWord.lenght() - 1);
            }
        }
    }
    catch (...)
    {
        std::cout << "Found!" << std::endl;
        auto firstElement = this->_result.back();
        this->_result.push_back(std::pair<char, DictionaryWord*> (*firstElement.second - this->_baseWord,
                                                                   &this->_baseWord));
        for (auto it = this->_result.rbegin();
             it != this->_result.rend();
             it ++)
        {
            std::cout << " + " << (*it).first  << " = " << (*it).second->word();
        }
        std::cout << std::endl;
    }
}

DictionaryWord &Dictionary::baseWord()
{
    return this->_baseWord;
}

void Dictionary::setBaseWord(const std::string &word)
{
    this->_baseWord = std::move(DictionaryWord(word));
    this->_maxWordSize = static_cast<int>(word.size());
}

Dictionary::Dictionary()
    : _baseWord (std::string(""))
    , _maxWordSize (0)
{

}

void Dictionary::findAnnagrams(const DictionaryWord &word, int depth) noexcept (false)
{
    if (this->_baseWord.lenght() == depth)
        throw std::invalid_argument("Found!");

    auto wordsByDepth = this->_records.equal_range(depth);

    for (auto it = wordsByDepth.first;
         it != wordsByDepth.second;
         it ++)
    {
        char addedLetter = word - (*it).second;
        if (addedLetter)
        {
            this->_result.push_back(std::pair<char, DictionaryWord*> (addedLetter, &((*it).second)));
            findAnnagrams((*it).second, depth - 1);
            this->_result.pop_back();
        }
    }
}
