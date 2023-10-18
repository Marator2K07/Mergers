#ifndef CHARFILE_H
#define CHARFILE_H

///
/// \brief The CharFile class
/// имитация файла с текстовыми данными
class CharFile
{
private:
    static int MaxLenght = 4096;
    int lenght;
    char data[MaxLenght] {' '};

public:
    CharFile();
};

#endif // CHARFILE_H
