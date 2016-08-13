#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

//!
//! \brief The anagram_found_exception class
//! Occurs when annagram transition was found
//!
class anagram_found_exception : std::exception
{
public:
    virtual const char* what() const noexcept {return "Found!";}
};

#endif // EXCEPTIONS_H
