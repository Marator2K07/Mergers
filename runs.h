#ifndef RUNS_H
#define RUNS_H

#include <QFile>
#include <QTextStream>

///
/// \brief The Runs class
/// Класс серий - упорядоченных послевательностей
class Runs
{
public:
    ///
    /// \brief openRandomSeq
    /// создает файл со случайным набором чисел
    static openRandomSeq(QString path,
                         QString name,
                         int lenght,
                         int seed);

    Runs();
};

#endif // RUNS_H
