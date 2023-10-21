#include "sequencesorting.h"

void SequenceSorting::NaturalMerge(QFile *src)
{
    int L = -1; // число серий после слияния
    QFile *f0;
    QFile *f1;
    QFile *f2;
    // создание бегунков для файлов выше
    Runner *r0 = new Runner;
    Runner *r1 = new Runner;
    Runner *r2 = new Runner;
    // инициализируем бегунок с помощью файла источника
    Runs::setRunner(r2, src, 0);

    //do {

        // инициализируем вспомогательные файлы
        f0 = Runs::newFile("D:", "f0.txt");
        f1 = Runs::newFile("D:", "f1.txt");
        // ставим бегунки в этих файлах на нулевые позиции
        Runs::setRunner(r0, f0, 0);
        Runs::setRunner(r1, f1, 0);

        // распределить последовательности из r2 в r0 и r1
        do {
            Runs::copyRun(r2, r0);
            if (!r2->getEof()) {
                Runs::copyRun(r2, r1);
            }
        } while (!r2->getEof());
        /*
        Runs::setRunner(r0, f0, 0);
        Runs::setRunner(r1 ,f1, 0);
        f2 = Runs::newFile("D:", "f2.txt");
        Runs::setRunner(r2, f2, 0);

    //} while (L != 1);

    */

}

SequenceSorting::SequenceSorting()
{
}
