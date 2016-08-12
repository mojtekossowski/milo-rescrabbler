#include <QtCore/QCoreApplication>
#include <QtCore/qglobal.h>
#include <QtDebug>
#include <iostream>
#include <chrono>

#include "dictionary.h"

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
    QCoreApplication a(argc, argv);

    // Parse user's input
    const QStringList arguments = a.arguments();

    int helpIndex = arguments.indexOf("--help");
    int defaultIndex = arguments.indexOf("--default");
    int dictIndex = arguments.indexOf("--dict");
    int beginIndex = arguments.indexOf("--begin");
    if (helpIndex > 0)
    {
        return displayHelp();
    }

    // Load benchmark
    auto t0 = std::chrono::high_resolution_clock::now();
    auto d = Dictionary::getInstance();
    if (beginIndex > 0)
    {
        std::string word;
        std::cout << "Enter beginning word: ";
        std::cin >> word;

        t0 = std::chrono::high_resolution_clock::now();
        d->setBaseWord(word);
    }
    if (defaultIndex > 0)
    {
        if (beginIndex < 0)
            d->setBaseWord("ail");

        if (dictIndex < 0)
        {
            std::vector<std::string> storedDict = {
                "ail", "tennis", "nails", "desk",
                "aliens", "table", "engine", "sail", "ailasndfaf"
            };

            d->parseDictionary(storedDict);
        }
        else
        {
            d->parseDictionary("./assets/words");
        }
    }
    else if (dictIndex > 0)
    {
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
    d->run();

    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

    std::cout << std::endl << "Operation took " << dt << " milliseconds." << std::endl;

    return 0;
}
