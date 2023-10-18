#include <QCoreApplication>

#include "runs.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Runs::openRandomSeq("D:","outR.txt", 22);

    return a.exec();
}
