#ifndef RUNS_H
#define RUNS_H

#include "runner.h"

#include <QDebug>
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
    static QFile* openRandomSeq(QString path,
                                QString name,
                                int lenght);

    static void set(Runner r,
                    QFile *file,
                    qint64 pos);

    Runs();
};

#endif // RUNS_H
