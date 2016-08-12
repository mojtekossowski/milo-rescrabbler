#include "dictionary.h"
#include <iostream>
#include <fstream>

#include "exceptions.h"

//!
//! \brief Dictionary::dictionarySingleton initialize to nullptr
//!
Dictionary *Dictionary::dictionarySingleton = nullptr;

//!
//! \brief Dictionary::getInstance instance not existst -> create (Singleton pattern)
//! \return
//!
Dictionary *Dictionary::getInstance()
{
    if (!dictionarySingleton)
        dictionarySingleton = new Dictionary();

    return dictionarySingleton;
}

//!
//! \brief Dictionary::parseDictionary method parses basic task dictionary
//! \param dictionary task dictionary
//!
void Dictionary::parseDictionary(const std::vector<std::string> &dictionary)
{
    std::cout << "Loading standard task dictionary" << std::endl;

    std::for_each(dictionary.begin(),
                  dictionary.end(),
                  [&] (const std::string &word)
    {
        this->addWordToDictionary(word);
    });
}

//!
//! \brief Dictionary::parseDictionary
//! \param filepath
//!
void Dictionary::parseDictionary(const std::string &filepath)
{
    std::cout << "Begin loading dictionary from " << filepath << "..." << std::endl;

    std::ifstream istream (filepath);
    std::string line;
    while (std::getline(istream, line))
    {
        if (line.empty())
            continue;

        this->addWordToDictionary(line);
    }
}

void Dictionary::clearDictionary()
{
    this->_records.clear();
}

void Dictionary::run()
{
    auto root = this->_records.begin();
    if (this->_baseWord.lenght() != (*root).first)
    {
        std::cout << std::endl << "Base word is not present :(" << std::endl << std::endl;
        return;
    }
    try
    {
        for (unsigned long i = this->_maxWordSize; i > this->_baseWord.lenght(); --i)
        {

            auto lastItem = this->_records.equal_range(i);

            for (auto it = lastItem.first;
                 it != lastItem.second;
                 it ++)
            {
                this->_result.clear();
                auto pWord = &(*it).second;
                this->_result.push_back(std::pair<char, DictionaryWord*> ('\0', pWord));
                this->findAnnagrams(pWord, pWord->lenght() - 1);
            }
        }

        std::cout << std::endl << "Not Found :(" << std::endl << std::endl;
    }
    catch (anagram_found_exception &)
    {
        auto firstElement = this->_result.back();

        std::cout << std::endl << "Found!" << std::endl << std::endl;
        std::cout << this->_baseWord.word() << " + " << *firstElement.second - this->_baseWord << " = ";

        for (auto it = this->_result.rbegin();
             it != this->_result.rend();
             it ++)
        {
            std::cout << (*it).second->word();
            if ((*it).first)
                std:: cout << " + " << (*it).first  << " = ";
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
    this->_maxWordSize = word.size();
}

Dictionary::Dictionary()
    : _baseWord (std::string(""))
    , _maxWordSize (0)
{

}

void Dictionary::findAnnagrams(DictionaryWord *word, unsigned long depth) noexcept (false)
{
    if (this->_baseWord.lenght() == depth)
        throw anagram_found_exception();

    auto wordsByDepth = this->_records.equal_range(depth);

    for (auto it = wordsByDepth.first;
         it != wordsByDepth.second;
         it ++)
    {
        char addedLetter = *word - (*it).second;
        if (addedLetter)
        {
            this->_result.push_back(std::pair<char, DictionaryWord*> (addedLetter, &((*it).second)));
            findAnnagrams(&(*it).second, depth - 1);
            this->_result.pop_back();
        }
    }
}

void Dictionary::addWordToDictionary(const std::string &word)
{
    try
    {
        if (word.length() < this->_baseWord.word().length())
            return;

        if ((word.length() == this->_baseWord.word().length()))
        {
            if (word != this->_baseWord.word())
                return;
        }

        auto record = DictionaryWord(word, this->_baseWord);
        this->_records.insert(std::pair<int, DictionaryWord> (word.size(), std::move(record)));
        this->_maxWordSize = std::max(this->_maxWordSize, word.size());
    }
    catch (...)
    {
        // Gotta catch'em all ;D
    }
}
