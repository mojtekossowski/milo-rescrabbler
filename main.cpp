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
        "aliens", "table", "engine", "sail", "ailasndfaf"
    };

    auto d = Dictionary::getInstance();
    d->setBaseWord("ail");
    std::cout << "Begin parsing dictionary" << std::endl;
    d->parseDictionary("/home/mojtek/Projects/milo-rescrabbler/assets/words");
    std::cout << "Begin Run Algorithm" << std::endl;
    d->run();

    return a.exec();
}
