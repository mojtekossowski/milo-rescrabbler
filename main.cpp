#include <QtCore/QCoreApplication>
#include <QtCore/qglobal.h>
#include <QtDebug>
#include <iostream>
#include <chrono>

#include "dictionary.h"

//!
//! \brief displayHelp
//! Displays help
//! \return grommet to return 0 in main
//!
int displayHelp()
{
    std::cout << "Commands:" << std::endl << std::endl
              << "    --dict <filepath>  loads file" << std::endl
              << "    --default          uses default dictionary (from task)" << std::endl
              << "    --begin <word>     sets begin world" << std::endl << std::endl
              << "Mix of commands will also work. ex. --dict --default will look " << std::endl
              << "for 'ail' in ./assets/words (unix dictionary from /usr/share/dict)" << std::endl << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    // Initialize QCoreApplication (console, for parsing arguments)
    QCoreApplication a(argc, argv);

    // Parse user's input
    const QStringList arguments = a.arguments();

    int helpIndex = arguments.indexOf("--help");
    int defaultIndex = arguments.indexOf("--default");
    int dictIndex = arguments.indexOf("--dict");
    int beginIndex = arguments.indexOf("--begin");

    // If help occured
    if (helpIndex > 0)
    {
        return displayHelp();
    }

    // Load benchmark
    auto t0 = std::chrono::high_resolution_clock::now();

    // Load dictionary Singleton
    auto d = Dictionary::getInstance();

    // If '--begin' option was specified - prompt
    // the lookop word from user.
    if (beginIndex > 0)
    {
        std::string word;
        std::cout << "Enter beginning word: ";
        std::cin >> word;

        t0 = std::chrono::high_resolution_clock::now();
        d->setBaseWord(word);
    }
    // If user wants to use default settings
    if (defaultIndex > 0)
    {
        // And not provides '--begin' option - assign 'ail' as baseWord
        if (beginIndex < 0)
            d->setBaseWord("ail");

        // If dictionary was not specified - load default dictionary
        if (dictIndex < 0)
        {
            std::vector<std::string> storedDict = {
                "ail", "tennis", "nails", "desk",
                "aliens", "table", "engine", "sail", "ailasndfaf"
            };

            // Begin parsing default dictionary
            d->parseDictionary(storedDict);
        }
        else
        {
            // Begin parsing dictionary from default (install) path
            d->parseDictionary("./assets/words");
        }
    }
    // If no default settings are present and user specifies '--dict' option
    else if (dictIndex > 0)
    {
        // If user has prompted the dictionary filepath
        if (dictIndex < arguments.size() - 1)
        {
            d->parseDictionary(arguments.at(dictIndex + 1).toStdString());
        }
        else
        {
            return displayHelp();
        }
    }
    else
    {
        return displayHelp();
    }

    std::cout << "Running algorithm..." << std::endl;

    // Perform lookup action
    d->run();

    // Measure benchmark time
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

    std::cout << std::endl << "Operation took " << dt << " milliseconds." << std::endl;

    return 0;
}
