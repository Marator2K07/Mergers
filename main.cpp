#include <QCoreApplication>

#include "sequencesorting.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile *newFile = Runs::openRandomSeq("D:","outR.txt", 22);
    SequenceSorting::distribute(newFile, "D:", 4);
    //QFile *result = SequenceSorting::BalancedMerge(newFile, "D:", 2);
    //result->remove();

    //Runner *r = new Runner();
    //Runs::setRunner(r, newFile, 0);
    //int *lol = new int;
    //Runs::writeIntToRunnerPos(r, 778);
    //Runs::readIntFromRunnerPos(r, *lol);
    //Runs::writeSeq(newFile);

    return a.exec();
}
