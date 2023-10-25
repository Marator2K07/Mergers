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
    // стартовая инициализация переменных массивов указателей
    for (int i = 0; i < N; ++i) {
        f[i] = new QFile;
        g[i] = new QFile;
        r[i] = new Runner;
        w[i] = new Runner;
    }

    // основной алгоритм начинается отсюда
    Runs::setRunner(R, src, 0);
    // создаем файл и ставим бегунок к нему
    for (int i = 0; i < N; ++i) {
        Runs::newFile(g[i], "D:", QString("%1_startSeq.txt").arg(i));
        Runs::setRunner(w[i], g[i], 0);
    }
    // распределяем начальные серии из src по файлам g[i]
    int j = 0; // вспомогательный индекс
    L = 0;
    do {
        do {
            Runs::copy(R, w[j]);
        } while (!R->getEor());
        L++;
        j++;
        if (j == N) {
            j = 0;
        }
    } while (!R->getEof());
    // процесс самого слияния
    // do {
        if (L < N) {
            k1 = L;
        } else {
            k1 = N;
        }
        K1 = k1;
        // устанавливаем бегунки источники
        for (int i = 0; i < k1; ++i) {
            Runs::setRunner(r[i], g[i], 0);
        }
        // устанавливаем бегунки приемники в свежий файл
        for (int i = 0; i < k1; ++i) {
            Runs::newFile(f[i], "D:", QString("%1_tempSeq.txt").arg(i));
            Runs::setRunner(w[i], f[i], 0);
        }
        // подготовка к слиянию
        for (int i = 0; i < k1; ++i) {
            t[i] = i;
        }
        L = 0;
        j = 0;
        // сливаем по одной серии из источников пока серии не закончатся
        int m; // вспомогательный индекс
        int o; // вспомогательный индекс
        int min; // наименьший ключ, для последующих вложенных итераций
        int x; // временное хранение
        do {
            L++;
            k2 = k1;
            // выбираем наименьший ключ и копируем его,
            // потом анализируем, был ли конец файла или серии,
            // в случае чего делаем необходимые преобразования
            do {
                m = 0;
                min = *r[t[0]]->getFirst();
                o = 1;
                while (o < k2) {
                    x = *r[t[o]]->getFirst();
                    if (x < min) {
                        min = x;
                        m = o;
                    }
                    o++;
                }
                Runs::copy(r[t[m]], w[j]);
                if (r[t[m]]->getEof()) {
                    k1--;
                    k2--;
                    t[m] = t[k2];
                    t[k2] = t[k1];
                } else if (r[t[m]]->getEor()) {
                    k2--;
                    int temp = t[m];
                    t[m] = t[k2];
                    t[k2] = temp;
                }
            } while (k2 != 0);
            j++;
            if (j == K1) {
                j = 0;
            }
        } while (k1 != 0);

    // } while (L != 1);
}

SequenceSorting::SequenceSorting()
{
}
