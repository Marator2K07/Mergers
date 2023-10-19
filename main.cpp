#include <QCoreApplication>

#include "runs.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile *newFile = Runs::openRandomSeq("D:","outR.txt", 22);
    Runner *r = new Runner();
    Runs::setRunner(r, newFile, 0);

    Runs::readIntFromRunnerPos(r, 5);
    Runs::writeIntFromRunnerPos(r, 0, 999);

    return a.exec();
}
