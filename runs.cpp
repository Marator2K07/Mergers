#include "runs.h"

QFile *Runs::openRandomSeq(QString path,
                           QString name,
                           int lenght)
{
    QString filePath = path + '/' + name;
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::WriteOnly  | QIODevice::Text))
        return nullptr;
    // если все успешно, можем писать случайную информацию в файл
    QTextStream out(file);
    for (int i = 0; i < lenght-1; ++i) {
        int randNumber = QRandomGenerator::global()->bounded(669);
        out << randNumber << ' ';
    }
    file->close();
    return file;
}

void Runs::set(Runner r,
               QFile *file,
               qint64 pos)
{
    // работы с бегунком
    r.setFile(file);
    r.setEof(false);
    if (r.getPos() >= 0) {
        if (r.getPos() <= file->size()) {
            r.setPos(pos);
        } else {
            r.setPos(file->size());
        }
    } else {
        r.setPos(0);
    }
    r.setEor(r.getEof());
    // считываем первое число из последовательности
    if (!file->open(QIODevice::ReadOnly  | QIODevice::Text))
        return;
    QTextStream in(file);
    QString firstNum;
    in >> firstNum;
    r.setFirst(std::stoi(firstNum));
}

Runs::Runs()
{
}
