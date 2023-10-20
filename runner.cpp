#include "runner.h"

QFile *Runner::getFile()
{
    return file;
}

void Runner::setFile(QFile *file)
{
    this->file = file;
}

qint64 Runner::getPos() const
{
    return pos;
}

void Runner::setPos(qint64 newPos)
{
    pos = newPos;
}

int *Runner::getFirst()
{
    return first;
}

void Runner::setFirst(int newFirst)
{
    if (first != nullptr) {
        *first = newFirst;
    }
}

bool Runner::getEof() const
{
    return eof;
}

void Runner::setEof(bool newEof)
{
    eof = newEof;
}

bool Runner::getEor() const
{
    return eor;
}

void Runner::setEor(bool newEor)
{
    eor = newEor;
}

void Runner::posMove(short shift)
{
    pos += shift;
}

Runner::Runner()
{
    first = new int;
}
