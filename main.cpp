#include <QCoreApplication>

#include "runs.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile *newFile = Runs::openRandomSeq("D:","outR.txt", 22);
    Runner *r = new Runner();
    Runs::setRunner(r, newFile, 0);

    int *lol = new int;
    Runs::writeIntToRunnerPos(r, 778);
    Runs::readIntFromRunnerPos(r, *lol);

    Runs::writeSeq(newFile);

    return a.exec();
}
