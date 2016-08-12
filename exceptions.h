#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class anagram_found_exception : std::exception
{
public:
    virtual const char* what() const noexcept {return "Found!";}
};

class anagram_not_matched : std::exception
{
public:
    virtual const char* what() const noexcept {return "Not matching.";}
};


#endif // EXCEPTIONS_H
