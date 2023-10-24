#include "sequencesorting.h"

void SequenceSorting::NaturalMerge(QFile *src)
{
    int L = -1; // число серий после слияния
    QFile *f0 = new QFile;
    QFile *f1 = new QFile;
    QFile *f2 = new QFile;
    // создание бегунков для файлов выше
    Runner *r0 = new Runner;
    Runner *r1 = new Runner;
    Runner *r2 = new Runner;
    // инициализируем бегунок с помощью файла источника
    Runs::setRunner(r2, src, 0);
    // основная часть алгоритма
    do {
        // инициализируем вспомогательные файлы
        Runs::newFile(f0, "D:", "f0.txt");
        Runs::newFile(f1, "D:", "f1.txt");
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
        Runs::newFile(f2, "D:", "result.txt");
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
        Runs::setRunner(r2, f2, 0);
    } while (L != 1);

    delete f0;
    delete f1;
    delete f2;

    delete r0;
    delete r1;
    delete r2;
}

void SequenceSorting::BalancedMerge(QFile *src, int N)
{
    // подготовка
    int L; // число распределенных серий
    int k1; // число источников
    int k2; // число реально доступных источников в данный момент
    int K1;
    int t[N]; // вспомогательный массив для отображения индексов
    Runner *R = new Runner; // бегунок для работы с входными данными
    // создание файлов приемников/источников
    QFile *f[N];
    QFile *g[N];
    // создание бегунков для файлов приемников/источников
    Runner *r[N];
    Runner *w[N];

    // основной алгоритм начинается отсюда
    Runs::setRunner(R, src, 0);
    // проинициализируем половину файлов и бегунков к ним
    for (int i = 0; i < N-1; ++i) {
        g[i] = new QFile;
        w[i] = new Runner;
        Runs::newFile(g[i], "D:", QString("%1_g.txt").arg(i));
        Runs::setRunner(w[i], g[i], 0);
    }
}

SequenceSorting::SequenceSorting()
{
}
