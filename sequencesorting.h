#ifndef SEQUENCESORTING_H
#define SEQUENCESORTING_H

#include "runs.h"

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
    static void BalancedMerge(QFile* src);

    SequenceSorting();
};

#endif // SEQUENCESORTING_H
