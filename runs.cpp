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
    QTextStream stream(file);
    for (int i = 0; i < lenght-1; ++i) {
        int randNumber = QRandomGenerator::global()->bounded(669);
        stream << randNumber << ' ';
    }
    file->close();
    return file;
}

void Runs::setRunner(Runner *runner,
                     QFile *file,
                     qint64 pos)
{
    // работы с бегунком
    runner->setFile(file);
    runner->setEof(false);
    if (runner->getPos() >= 0) {
        if (runner->getPos() <= file->size()) {
            runner->setPos(pos);
        } else {
            runner->setPos(file->size());
        }
    } else {
        runner->setPos(0);
    }
    runner->setEor(runner->getEof());
    runner->setFirst(new int);
    // считываем первое число из последовательности
    Runs::readIntFromRunnerPos(runner, *runner->getFirst());
}

void Runs::readIntFromRunnerPos(Runner *runner, int &num)
{
    QFile *file = runner->getFile();
    if (file == nullptr)
        return;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    // считываем число с текущей позиции
    QTextStream stream(file);
    QString thisNum;
    if (file->seek(runner->getPos())) {
        stream >> thisNum;
    } else {
        thisNum = "-1";
    }

    file->close();
    num = stoi(thisNum.toStdString());
}

void Runs::writeIntToRunnerPos(Runner *runner, int num)
{
    QFile *file = runner->getFile();
    if (file == nullptr)
        return;
    if (!file->open(QIODevice::WriteOnly |
                    QIODevice::Text |
                    QIODevice::Append))
        return;
    // пишем заданное число в текущую позицию
    QTextStream stream(file);
    if (file->seek(runner->getPos())) {
        stream << num << ' ';
    }

    file->close();
}

void Runs::copy(Runner *src, Runner *dest)
{
    dest->setFirst(src->getFirst());
    Runs::writeIntToRunnerPos(dest, *dest->getFirst());
    Runs::readIntFromRunnerPos(src, *src->getFirst());
    src->setEor(src->getEof() || (*src->getFirst() < *dest->getFirst()));
}

Runs::Runs()
{
}
