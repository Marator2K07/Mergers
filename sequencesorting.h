#ifndef SEQUENCESORTING_H
#define SEQUENCESORTING_H

#include "runs.h"
#include <QQueue>

///
/// \brief The SequenceSorting class
/// класс со статическими методами сортировки последовательностей
class SequenceSorting
{
public:
    ///
    /// \brief NaturalMerge
    /// сортировка естественными слияниями
    static void NaturalMerge(QFile *src);

    ///
    /// \brief BalancedMerge
    /// сортировка сбалансированными слияниями
    static void BalancedMerge(QFile* src, int N);

    SequenceSorting();
};

#endif // SEQUENCESORTING_H
