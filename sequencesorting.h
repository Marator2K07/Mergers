#ifndef SEQUENCESORTING_H
#define SEQUENCESORTING_H

#include "runs.h"
#include <QQueue>

using std::vector;

///
/// \brief The SequenceSorting class
/// класс со статическими методами сортировки последовательностей
/// исключение - приватный статический метод просеивания массива sift
/// для усовершенствования некоторых алгоритмов
class SequenceSorting
{
private:
    ///
    /// \brief sift
    /// метод просеивания массива до состояния
    /// двоичной кучи (условной пирамиды), в нашем случае
    /// этот метод будет использоваться в усовершенствованном
    /// алгоритме многофазной сортировки - в методе distribute
    static void sift(int l,
                     int r,
                     int heap[]);

public:
    ///
    /// \brief naturalMerge
    /// сортировка естественными слияниями
    static void naturalMerge(QFile *src);

    ///
    /// \brief balancedMerge
    /// сортировка сбалансированными слияниями
    static QFile *balancedMerge(QFile* src,
                                QString path,
                                int N);

    ///
    /// \brief polyphase
    /// сортировка последовательностей
    /// многофазным способом
    static QFile *polyphase(QFile* src,
                            QString path,
                            int N);

    ///
    /// \brief distribute
    /// метод распределения начальных ключей по сериям
    /// в файлы, причем количество серий зависит от передаваемого
    /// размера пирамиды. Демонстрирует то, что некоторые участки
    /// алгоритмов при сортировке последовательностей (файлов)
    /// можно решать с помощью оперативной памяти (массивов)
    /// при наличии оной.
    static vector<QString> distribute(QFile *src,
                                      QString path,
                                      short heapSize = 16);

    SequenceSorting();
};

#endif // SEQUENCESORTING_H
