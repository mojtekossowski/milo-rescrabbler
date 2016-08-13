#include "dictionary.h"
#include <iostream>
#include <fstream>

#include "exceptions.h"

//!
//! \brief Dictionary::dictionarySingleton
//! Initialize singleton to nullptr at startup
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
//! \brief Dictionary::parseDictionary
//! Parses default dictionary contained in vector
//! \param dictionary Task dictionary
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
//! Parses dictionary from file (specified by user or defaulted)
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

//!
//! \brief Dictionary::clearDictionary
//! Clears dictionary
void Dictionary::clearDictionary()
{
    this->_records.clear();
}

//!
//! \brief Dictionary::run
//! The algorithm execution method.
//! Performs #2 stage of algorithm described in readme.md file
//! \details
//! Iteration through the multimap (_records) is performed
//! in descending order. For each element, the recursive
//! findAnnagrams function is called with the last longest word
//! with depth (word_size - 1). For each iteration the _record
//! list is cleared and filled in.
//!
void Dictionary::run()
{
    // Load the first DictionaryWord (should be base word if occured in Dictionary)
    auto root = this->_records.begin();
    // For baseWord length only the dict's base word should be inserted
    if (this->_baseWord.lenght() != (*root).first)
    {
        std::cout << std::endl << "Base word is not present :(" << std::endl << std::endl;
        return;
    }
    try
    {
        for (unsigned long i = this->_maxWordSize; i > this->_baseWord.lenght(); --i)
        {
            // Obtain the elements with specified length (by common key)
            auto lastItem = this->_records.equal_range(i);

            // And iterathe through them
            for (auto it = lastItem.first;
                 it != lastItem.second;
                 it ++)
            {
                // Clear, PushToList, call findAnnagrams recursive with descent depth
                this->_result.clear();
                auto pWord = &(*it).second;
                this->_result.push_back(std::pair<char, DictionaryWord*> ('\0', pWord));
                this->findAnnagrams(pWord, pWord->lenght() - 1);
            }
        }

        // Walked for whole dictionary - no result
        std::cout << std::endl << "Not Found :(" << std::endl << std::endl;
    }
    catch (anagram_found_exception &)
    {
        // If exception was raised - anagram transition was found.
        // For now, at the top exist the longest anagram with no transit letter.
        // Its necessary to find the first transit letter because exception was raised
        // if the current depth was reaching the lenght of base word (base word is not listed)
        auto firstElement = this->_result.back();

        std::cout << std::endl << "Found!" << std::endl << std::endl;

        // Substract to obtain the transit letter between last element and base word...
        std::cout << this->_baseWord.word() << " + " << *firstElement.second - this->_baseWord << " = ";

        // Prompt transit
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

//!
//! \brief Dictionary::depth
//! \return Depth of found anagrams
//!
unsigned long Dictionary::depth() const
{
    return this->_result.size();
}

//!
//! \brief Dictionary::baseWord
//! \return
//!
DictionaryWord &Dictionary::baseWord()
{
    return this->_baseWord;
}

//!
//! \brief Dictionary::setBaseWord
//! \param word
//!
void Dictionary::setBaseWord(const std::string &word)
{
    this->_baseWord = std::move(DictionaryWord(word));
    this->_maxWordSize = word.size();
}

//!
//! \brief Dictionary::Dictionary
//!
Dictionary::Dictionary()
    : _baseWord (std::string(""))
    , _maxWordSize (0)
{

}

//!
//! \brief Dictionary::findAnnagrams
//! Performs #3 stage of algorithm described in readme.md file.
//! Recursive method.
//! \details findAnnagrams method searches the dictionary with specified depth
//! and substract all obtained elements from dictionary word argument. If
//! there's a possible transition (exists a transit letter between two elements)
//! the word is pushed to the result list. If not - its poped out. When the base word
//! was found in dictionary, the 'anagram_found_exception' is raised
//! \param word Current word (depth+1)
//! \param depth Current depth
//!
void Dictionary::findAnnagrams(DictionaryWord *word, unsigned long depth) noexcept (false)
{
    // For baseWord length only the dict's base word should be inserted
    if (this->_baseWord.lenght() == depth)
        throw anagram_found_exception(); // found - throw exception - rollback

    // Find all words by depth (common key - current depth)
    auto wordsByDepth = this->_records.equal_range(depth);

    for (auto it = wordsByDepth.first;
         it != wordsByDepth.second;
         it ++)
    {
        // Try to find transient letter by calling operator-()
        char addedLetter = *word - (*it).second;
        if (addedLetter)
        {
            // If exists - push transient letter and current loop word to list
            this->_result.push_back(std::pair<char, DictionaryWord*> (addedLetter, &((*it).second)));
            // Call findAnnagrams recursively
            findAnnagrams(&(*it).second, depth - 1);
            // If exception was not thrown - pop stack.
            this->_result.pop_back();
        }
    }
}

//!
//! \brief Dictionary::addWordToDictionary
//! Performs #1 stage of algorithm described in readme.md file.
//! \details This method adds word from file/default settings to dictionary.
//! For assumption, the baseWord has the shortest length
//! And words with the same or smaller length should be
//! not added to dictionary. Only the word which LettersStack covers
//! the baseWord stack should be added (and the base word itself, if occured).
//! \param word
//!
void Dictionary::addWordToDictionary(const std::string &word)
{
    try
    {
        // If the word lenght is smaller than the baseWord length - ommit record
        if (word.length() < this->_baseWord.word().length())
            return;

        // If the word lenght is equal to the baseWord length
        // and it is not the base word - ommit record
        if ((word.length() == this->_baseWord.word().length()))
        {
            if (word != this->_baseWord.word())
                return;
        }

        // Try to creade Dictionary word regarding to base word
        auto record = DictionaryWord(word, this->_baseWord);
        // If no exception was thrown - move the record to multimap.
        this->_records.insert(std::pair<int, DictionaryWord> (word.size(), std::move(record)));
        // Updae max word size
        this->_maxWordSize = std::max(this->_maxWordSize, word.size());
    }
    catch (anagram_not_matched &)
    {
        // If word doesn't contains all letters of BaseWord...
        // Do nothing, rollback stack and try to parse next word from dictionary ;)
    }
}
