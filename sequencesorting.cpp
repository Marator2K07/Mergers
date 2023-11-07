#include "sequencesorting.h"

void SequenceSorting::sift(int l,
                           int r,
                           int heap[])
{
    int i = l;
    int j = 2*l+1;
    int x = heap[i]; // запоминаем верхушку пирамиды/подпирамиды
    // после этой строки индекс будет указывать на наибольшего потомка
    if (j < r && heap[j] > heap[j+1]) {
        j++;
    }
    // само "просеивание"
    while (j <= r && x > heap[j]) {
        // ставим наибольший элемент наверх,
        // устанавливаем новые границы
        heap[i] = heap[j];
        i = j;
        j = 2*j+1;
        // снова, как и в начале выбираем наибольший потомок
        if (j < r && heap[j] > heap[j+1]) {
            j++;
        }
    }
    heap[i] = x;
}

void SequenceSorting::naturalMerge(QFile *src)
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

QFile *SequenceSorting::balancedMerge(QFile *src,
                                      QString path,
                                      int N)
{
    // подготовка
    int progress; // номер итерации основного цикла слияния
    int L; // число распределенных серий
    int k1; // число источников
    int k2; // число реально доступных источников в данный момент
    int t[N]; // вспомогательный массив для отображения индексов
    Runner *R = new Runner; // бегунок для работы с входными данными
    // создание файлов источников и приемников
    QFile *srcFiles[N];
    QFile *rcvrFiles[N];
    // создание бегунков для файлов источников и приемников
    Runner *srcRunners[N];
    Runner *rcvrRunners[N];    

    // стартовая инициализация переменных массивов указателей
    for (int i = 0; i < N; ++i) {
        srcFiles[i] = new QFile;
        rcvrFiles[i] = new QFile;
        srcRunners[i] = new Runner;
        rcvrRunners[i] = new Runner;
    }
    // также для будущей очистки ненужных файлов используем очередь
    QQueue<QString> oldFiles;

    // основной алгоритм начинается отсюда
    Runs::setRunner(R, src, 0);
    // создаем файл и ставим бегунок к нему
    for (int i = 0; i < N; ++i) {
        Runs::newFile(srcFiles[i], path, QString("0_%1_Seq.txt").arg(i));
        Runs::setRunner(rcvrRunners[i], srcFiles[i], 0);
    }
    // распределяем начальные серии из src по файлам srcFiles[i]
    int j = 0; // вспомогательный индекс
    L = 0;
    do {
        do {
            Runs::copy(R, rcvrRunners[j]);
        } while (!R->getEor());
        L++;
        j++;
        if (j == N) {
            j = 0;
        }
    } while (!R->getEof());
    // процесс самого слияния (основной цикл слияния)
    int K1; // временное хранение
    progress = 0;
    do {
        if (L < N) {
            k1 = L;
        } else {
            k1 = N;
        }
        K1 = k1;
        // устанавливаем бегунки источники в прошлый файл и
        // кидаем названия файлов, которые в будущем устареют,
        // в очередь
        for (int i = 0; i < k1; ++i) {
            QString fileName = QString("%1_%2_Seq.txt").
                               arg(progress).arg(i);
            Runs::setFile(srcFiles[i], path, fileName);
            Runs::setRunner(srcRunners[i], srcFiles[i], 0);
            oldFiles.append(fileName);
        }
        // устанавливаем бегунки приемники в свежий файл
        for (int i = 0; i < k1; ++i) {
            Runs::newFile(rcvrFiles[i], path, QString("%1_%2_Seq.txt").
                                              arg(progress+1).arg(i));
            Runs::setRunner(rcvrRunners[i], rcvrFiles[i], 0);
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
                min = *srcRunners[t[0]]->getFirst();
                o = 1;
                while (o < k2) {
                    x = *srcRunners[t[o]]->getFirst();
                    if (x < min) {
                        min = x;
                        m = o;
                    }
                    o++;
                }
                Runs::copy(srcRunners[t[m]], rcvrRunners[j]);
                if (srcRunners[t[m]]->getEof()) {
                    k1--;
                    k2--;
                    t[m] = t[k2];
                    t[k2] = t[k1];
                } else if (srcRunners[t[m]]->getEor()) {
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
        progress++;
    } while (L != 1);

    // подготовка ответа
    QFile *resultFile = new QFile;
    resultFile->setFileName(rcvrFiles[0]->fileName());

    // чистка временных файлов
    foreach (QString file, oldFiles) {
        Runs::newFile(srcFiles[0], path, file);
        oldFiles.dequeue();
    }
    // освобождение памяти
    for (int i = 0; i < N; ++i) {
        delete srcFiles[i];
        delete rcvrFiles[i];
        delete srcRunners[i];
        delete rcvrRunners[i];
    }
    return resultFile;
}

QFile *SequenceSorting::polyphase(QFile *src,
                                  QString path,
                                  int N)
{
    // подготовка
    int j; // индекс текущей принимающей последовательности
    int &jRef {j}; // ссылка на него
    int level; // номер уровня распределения последовательностей
    int &levelRef {level}; // ссылка на него
    int a[N]; // массив для отображения идеального количества серий на опр. шаге
    int d[N]; // массив для отображения фиктивного числа серий в определенной итерации
    int ta[N]; // вспомогательный массив индексов для реальных серий
    int t[N]; // вспомогательный массив для индексов
    Runner *R = new Runner; // бегунок для работы с входными данными
    QFile *result; // переменная под ответ
    // создание файлов и бегунков к ним
    QFile *files[N];
    Runner *runners[N];

    // стартовая инициализация переменных массивов указателей
    for (int i = 0; i < N; ++i) {
        files[i] = new QFile;
        runners[i] = new Runner;
    }

    // сам алгоритм начинается отсюда
    Runs::setRunner(R, src, 0); // ставим бегунок к основному файлу
    // начальная инициализация и подготовка к организованному
    // распределению последовательностей из файла-источника
    for (int i = 0; i < N-1; ++i) {
        a[i] = 1;
        d[i] = 1;
        QString fileName = QString("[%1]_Seq.txt").arg(i);
        Runs::newFile(files[i], path, fileName);
        Runs::setRunner(runners[i], files[i], 0);
    }
    // распределяем начальные серии из файла источника
    level = 1;
    j = 0;
    a[N-1] = 0;
    d[N-1] = 0;
    do {
        Runs::selectRunsReceiver(a, d, N, jRef, levelRef);
        Runs::copyRun(R, runners[j]);
    } while (!R->getEof() && j != N-2);
    // распределяем оставшиеся серии по определенным правилам,
    // причем избегаем случайной склейки серий!
    while (!R->getEof()) {
        Runs::selectRunsReceiver(a, d, N, jRef, levelRef);
        if (*runners[j]->getFirst() <= *R->getFirst()) {
            Runs::copyRun(R, runners[j]);
            if (R->getEof()) {
                d[j]++;
            } else {
                Runs::copyRun(R, runners[j]);
            }
        } else {
            Runs::copyRun(R, runners[j]);
        }
    }
    // инициализируем массив вспомогательных индексов и обновляем бегунки
    for (int i = 0; i < N-1; ++i) {
        t[i] = i;
        Runs::setRunner(runners[i], files[i], 0);
    }
    t[N-1] = N-1; // не забываем про последний индекс
    // далее - сам процесс слияния - сливаем из t[0]...t[N-2] в t[N-1]
    // в каждый момент времени, один из всех файлов - является
    // приемником, до тех пор, пока любой другой не опустеет ->
    // в этом случае он становиться приемником.
    do {
        int realRunsCount = a[N-2];
        d[N-1] = 0;
        // инициализируем файл для приема серий
        QString fileName = QString("[%1]_Seq.txt").arg(t[N-1]);
        Runs::newFile(files[t[N-1]], path, fileName);
        Runs::setRunner(runners[t[N-1]], files[t[N-1]], 0);
        result = files[t[N-1]]; // ставим метку ответа
        // сливаем одну серию
        do {
            // обработка фиктивной части
            int realRunsIndex = 0;
            for (int i = 0; i < N-1; ++i) {
                if (d[i] > 0) {
                    d[i]--;
                } else {
                    ta[realRunsIndex] = t[i];
                    realRunsIndex++;
                }
            }
            // если не было ни одной реальной серии
            // то делаем вид, что записали фиктивную в приемник
            if (realRunsIndex == 0) {
                d[N-1]++;
            }
            // в остальных случаях сливаем одну реальную серию
            else {
                do {
                    int minIndex = 0;
                    int min = *runners[ta[0]]->getFirst();
                    int i = 1;
                    while (i < realRunsIndex) {
                        int x = *runners[ta[i]]->getFirst();
                        if (x < min) {
                            min = x;
                            minIndex = i;
                        }
                        i++;
                    }
                    Runs::copy(runners[ta[minIndex]], runners[t[N-1]]);
                    if (runners[ta[minIndex]]->getEor()) {
                        ta[minIndex] = ta[realRunsIndex-1];
                        realRunsIndex--;
                    }
                } while (realRunsIndex != 0);
            }
            realRunsCount--;
        } while (realRunsCount != 0);
        // ротация последовательностей, в данном случае, после того,
        // как какой-то из файлов закончился (цикл выше), мы останавливаемся
        // и производим подготовительные меры для следующего уровня.
        Runs::setRunner(runners[t[N-1]], files[t[N-1]], 0);
        int tTemp = t[N-1];
        int dTemp = d[N-1];
        realRunsCount = a[N-2];
        for (int i = N-1; i > 0; --i) {
            t[i] = t[i-1];
            d[i] = d[i-1];
            a[i] = a[i-1] - realRunsCount;
        }
        t[0] = tTemp;
        d[0] = dTemp;
        a[0] = realRunsCount;
        level--;
    } while (level != 0);

    // освобождение памяти и чистка файлов,
    // удаляем все кроме файла ответа
    for (int i = 0; i < N; ++i) {
        if (files[i] != result) {
            QString fileName = QString("[%1]_Seq.txt").arg(i);
            Runs::newFile(files[i], path, fileName);
            delete files[i];
        }
        delete runners[i];
    }

    return result;
}

void SequenceSorting::distribute(QFile *src,
                                 QString path,
                                 int N)
{
    // подготовка
    const int m = 16; // размер массива для пирамиды
    int mh = m / 2; // размер (высота) пирамиды
    int heap[m]; // сама куча (пирамида)
    int x; // буффер для работы с пирамидой
    int &xRef {x}; // ссылка на него
    int l; // левая граница нужного участка массива
    int r; // правая граница нужного участка массива
    // создание и инициализация файла и бегунков
    QFile *destFile = new QFile(); // файл с будущим ответом
    Runner *runnerR = new Runner();
    Runner *runnerW = new Runner();

    // алгоритм начинается отсюда
    // подготовка файлов и бегунков
    Runs::setRunner(runnerR, src, 0); // ставим бегунок на файл-источник
    Runs::newFile(destFile, path, "destination.txt");
    Runs::setRunner(runnerW, destFile, 0); // ставим бегунок на файл-приемник
    // 1) заполняем верхнюю половину пирамиды
    l = m;
    do {
        l--;
        Runs::readIntFromRunnerPos(runnerR, heap[l], true);
    } while (l != mh);
    // 2) теперь заполняем нижнюю часть пирамиды
    do {
        l--;
        Runs::readIntFromRunnerPos(runnerR, heap[l], true);
        SequenceSorting::sift(l, m-1, heap);
    } while (l != 0);
    // 3) пропускаем/просеиваем элементы сквозь пирамиду
    l = m;
    Runs::readIntFromRunnerPos(runnerR, xRef, true);
    while (!runnerR->getEof()) {
        Runs::writeIntToRunnerPos(runnerW, heap[0], true);
        // x - принадлежит той же серии
        if (heap[0] <= x) {
            heap[0] = x;
            SequenceSorting::sift(0, l-1, heap);
        }
        // иначе начать новую серию
        else {
            l--;
            heap[0] = heap[l];
            SequenceSorting::sift(0, l-1, heap);
            heap[l] = x;
            if (l < mh) {
                SequenceSorting::sift(l, m-1, heap);
            }
            // переполнение пирамиды, необходимо начать новую серию
            if (l == 0) {
                l = m;
            }
        }
        Runs::readIntFromRunnerPos(runnerR, xRef, true);
    }
    // 4) сброс нижней части пирамиды
    r = m;
    do {
        l--;
        Runs::writeIntToRunnerPos(runnerW, heap[0], true);
        heap[0] = heap[l];
        SequenceSorting::sift(0, l-1, heap);
        r--;
        heap[l] = heap[r];
        if (l < mh) {
            SequenceSorting::sift(l, r-1, heap);
        }
    } while (l != 0);
    // 5) сброс оставшейся верхней части пирамиды
    while (r > 0) {
        Runs::writeIntToRunnerPos(runnerW, heap[0], true);
        heap[0] = heap[r];
        r--;
        SequenceSorting::sift(0, r, heap);
    }
}

SequenceSorting::SequenceSorting()
{
}
