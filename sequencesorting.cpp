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
        // распределяем последовательности из r2 в r0 и r1
        do {
            Runs::copyRun(r2, r0);
            if (!r2->getEof()) {
                Runs::copyRun(r2, r1);
            }
        } while (!r2->getEof());
        // подготовка перед будущим слиянием файлов
        Runs::setRunner(r0, f0, 0);
        Runs::setRunner(r1 ,f1, 0);
        f2 = Runs::newFile("D:", "result.txt");
        Runs::setRunner(r2, f2, 0);
        // сливаем из r0 и r1 в r2
        L = 0;
        do {
            do {
                if (*r0->getFirst() < *r1->getFirst()) {
                    Runs::copy(r0, r2);
                    if (r0->getEor())
                        Runs::copyRun(r1, r2);
                } else {
                    Runs::copy(r1, r2);
                    if (r1->getEor())
                        Runs::copyRun(r0, r2);
                }
            } while (!r0->getEor() && !r1->getEor());
            L++;
        } while (!r0->getEof() && !r1->getEof());
        // копируем остатки
        while (!r0->getEof()) {
            Runs::copyRun(r0, r2);
            L++;
        }
        while (!r1->getEof()) {
            Runs::copyRun(r1, r2);
            L++;
        }

    //} while (L != 1);

    //f0->remove();
    //f1->remove();
    //f2->remove();

}

SequenceSorting::SequenceSorting()
{
}
