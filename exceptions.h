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

//!
//! \brief The anagram_not_matched class
//! Occurs when word obtained from dictionary
//! doesn't match the >>baseWord<<
//!
class anagram_not_matched : std::exception
{
public:
    virtual const char* what() const noexcept {return "Not matching.";}
};


#endif // EXCEPTIONS_H
