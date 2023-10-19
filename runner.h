#ifndef RUNNER_H
#define RUNNER_H

#include <QFile>

class Runner
{
private:
    QFile file;
    qint64 pos; // текущая позиция бегунка
    int first; // первый элемент в еще непрочитанной части файла
    bool eof; // конец ли это файла
    bool eor; // конец ли это последовательности

public:
    Runner();

    QFile getFile() const;
    void setFile(const QFile &newFile);
    qint64 getPos() const;
    void setPos(qint64 newPos);
    int getFirst() const;
    void setFirst(int newFirst);
    bool getEof() const;
    void setEof(bool newEof);
    bool getEor() const;
    void setEor(bool newEor);
};

#endif // RUNNER_H
