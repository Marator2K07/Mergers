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
    // считываем первое число из последовательности
    qint32 result = Runs::readIntFromRunnerPos(runner, 0);
    if (result != -1) {
        runner->setFirst(result);
    } else {
        runner->setFirst(0);
    }
}

qint32 Runs::readIntFromRunnerPos(Runner *runner, int pos)
{
    QFile *file = runner->getFile();
    if (file == nullptr)
        return -1;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    // считываем число с указанной позиции
    QTextStream stream(file);
    QString thisNum;
    if (file->seek(pos)) {
        stream >> thisNum;
    } else {
        thisNum = "-1";
    }

    file->close();
    return stoi(thisNum.toStdString());
}

void Runs::writeIntFromRunnerPos(Runner *runner,
                                 int pos,
                                 int num)
{
    QFile *file = runner->getFile();
    if (file == nullptr)
        return;
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    // пишем заданное число в указанную позицию
    QTextStream stream(file);
    if (file->seek(pos)) {
        stream << num << ' ';
    }

    file->close();
}

void Runs::copy(Runner *src, Runner *dest)
{
    // dest->setFirst(src->getFirst());

}

Runs::Runs()
{
}
