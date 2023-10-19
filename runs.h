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
    /// \brief openRandomSeq
    /// создает файл со случайным набором чисел
    static QFile* openRandomSeq(QString path,
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
    static void readIntFromRunnerPos(Runner *runner, int *num);

    ///
    /// \brief writeIntFromRunnerPos
    /// запись числа в текущую позицию ползунка файла
    static void writeIntToRunnerPos(Runner *runner, int num);

    static void copy(Runner *src, Runner *dest);

    Runs();
};

#endif // RUNS_H
