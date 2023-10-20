#ifndef RUNNER_H
#define RUNNER_H

#include <QFile>

class Runner
{
private:
    QFile *file;
    qint64 pos; // текущая позиция бегунка
    int *first; // первый элемент в еще непрочитанной части файла
    bool eof; // конец ли это файла
    bool eor; // конец ли это последовательности

public:
    Runner();

    QFile *getFile();
    void setFile(QFile *file);
    qint64 getPos() const;
    void setPos(qint64 newPos);
    int *getFirst();
    void setFirst(int *newFirst);
    bool getEof() const;
    void setEof(bool newEof);
    bool getEor() const;
    void setEor(bool newEor);

    void posMove(short shift);
};

#endif // RUNNER_H
