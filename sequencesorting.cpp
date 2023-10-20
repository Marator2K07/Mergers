#include "sequencesorting.h"

void SequenceSorting::NaturalMerge(QFile *src)
{
    int L; // число серий после слияния
    QFile *f0;
    QFile *f1;
    QFile *f2;
    // создание бегунков для файлов выше
    Runner *r0 = new Runner;
    Runner *r1 = new Runner;
    Runner *r2 = new Runner;
    // инициализируем бегунок с помощью файла источника
    Runs::setRunner(r2, src, 0);
    do {

    } while (L != 1);
}

SequenceSorting::SequenceSorting()
{
}
