#include "runner.h"

QFile Runner::getFile() const
{
    return file;
}

void Runner::setFile(const QFile &newFile)
{
    file = newFile;
}

qint64 Runner::getPos() const
{
    return pos;
}

void Runner::setPos(int newPos)
{
    pos = newPos;
}

int Runner::getFirst() const
{
    return first;
}

void Runner::setFirst(int newFirst)
{
    first = newFirst;
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

Runner::Runner()
{

}
