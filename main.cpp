#include <QtCore/QCoreApplication>
#include <QtCore/qglobal.h>
#include <QtDebug>
#include <iostream>

#include "dictionary.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<std::string> storedDict = {
        "ail", "tennis", "nails", "desk",
        "aliens", "table", "engine", "sail"
    };

    auto d = Dictionary::getInstance();
    d->setBaseWord("ail");
    d->parseDictionary(storedDict);
    d->run();

    return a.exec();
}
