#ifndef RUNS_H
#define RUNS_H

#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

///
/// \brief The Runs class
/// Класс серий - упорядоченных послевательностей
class Runs
{
public:
    ///
    /// \brief openRandomSeq
    /// создает файл со случайным набором чисел
    static void openRandomSeq(QString path,
                              QString name,
                              int lenght);

    Runs();
};

#endif // RUNS_H
