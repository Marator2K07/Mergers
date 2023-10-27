#ifndef RUNS_H
#define RUNS_H

#include "runner.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

using namespace std;

///
/// \brief The Runs class
/// Класс серий - упорядоченных послевательностей
class Runs
{
public:
    ///
    /// \brief newFile
    /// метод инициализации нового файла
    static void newFile(QFile *file,
                        QString path,
                        QString name);

    ///
    /// \brief setFile
    /// метод выбора файла через его путь/имя
    static void setFile(QFile *file,
                        QString path,
                        QString name);

    ///
    /// \brief openRandomSeq
    /// создает файл со случайным набором чисел
    static QFile *openRandomSeq(QString path,
                                QString name,
                                int lenght);

    ///
    /// \brief setRunner
    /// метод инициализации бегунка с переданным файлом
    static void setRunner(Runner *runner,
                          QFile *file,
                          qint64 pos);

    ///
    /// \brief readIntFromRunnerPos
    /// чтение числа из файла с текущей позиции
    static void readIntFromRunnerPos(Runner *runner,
                                     int &num,
                                     bool posMove = false);

    ///
    /// \brief writeIntFromRunnerPos
    /// запись числа в текущую позицию ползунка файла
    static void writeIntToRunnerPos(Runner *runner,
                                    int num,
                                    bool posMove = false);

    ///
    /// \brief copy
    /// копирование одного элемента из файла в другой
    static void copy(Runner *src, Runner *dest);

    ///
    /// \brief copyRun
    /// копирование серии в последовательности
    static void copyRun(Runner *src, Runner *dest);

    ///
    /// \brief selectRunsReceiver
    /// выбор приемника для очередной серии
    /// используется только для многофазной сортировки
    static void selectRunsReceiver(int a[],
                                   int d[],
                                   int arrSize,
                                   int &j,
                                   int &level);

    ///
    /// \brief writeSeq
    /// вывод текущего файла с метками уже
    /// отсортированных частей для этой последовательности
    /// чисел
    static void writeSeq(QFile *file);

    Runs();
};

#endif // RUNS_H
