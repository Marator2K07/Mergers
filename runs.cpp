#include "runs.h"

QFile *Runs::newFile(QString path, QString name)
{
    QString filePath = path + '/' + name;
    return new QFile(filePath);
}

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
    runner->setFirst(0);
    // считываем первое число из последовательности
    Runs::readIntFromRunnerPos(runner, *runner->getFirst());
}

void Runs::readIntFromRunnerPos(Runner *runner,
                                int &num,
                                bool posMove)
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
        if (posMove)
            runner->posMove(QString::number(num).length()+1);
    } else {
        thisNum = "-1";
    }

    file->close();
    num = stoi(thisNum.toStdString());
}

void Runs::writeIntToRunnerPos(Runner *runner,
                               int num,
                               bool posMove)
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
    // смещаем позицию далее после записи в эту позицию
    if (posMove)
        runner->posMove(QString::number(num).length()+1);

    file->close();
}

void Runs::copy(Runner *src, Runner *dest)
{
    dest->setFirst(*src->getFirst());
    Runs::writeIntToRunnerPos(dest, *dest->getFirst(), true);
    Runs::readIntFromRunnerPos(src, *src->getFirst(), true);
    src->setEor(src->getEof() || (*src->getFirst() < *dest->getFirst()));
}

void Runs::copyRun(Runner *src, Runner *dest)
{
    do {
        Runs::copy(src, dest);
    } while (!src->getEor());
}

void Runs::writeSeq(QFile *file)
{
    if (file == nullptr)
        return;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    // начальная инициализация переменных
    QString x;
    QString y = ".";
    int n = 0;
    int k = 0;
    // ввод результата в с указанием!!! уже отсортированных
    // последовательностей
    QString seq; // строка с результатом
    QTextStream stream(file);
    stream >> x;
    while (!stream.atEnd()) {
        seq.append(x);
        k++;
        stream >> y;
        if (y == "") {
            continue;
        }

        if (stoi(y.toStdString()) < stoi(x.toStdString())) {
            seq.append('|');
            n++;
        }
        x = y;
        seq.append(' ');
    }
    // вывод результата
    qDebug() << '$' << k << ' ' << n;
    qDebug() << seq;
}

Runs::Runs()
{
}
