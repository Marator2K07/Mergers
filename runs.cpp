#include "runs.h"

void Runs::newFile(QFile *file,
                   QString path,
                   QString name)
{
    QString filePath = path + '/' + name;
    // очищаем файл в любом случае
    file->setFileName(filePath);
    file->remove();
}

void Runs::setFile(QFile *file,
                   QString path,
                   QString name)
{
    QString filePath = path + '/' + name;
    file->setFileName(filePath);
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
    if (file->size() >= pos && pos >= 0) {
        runner->setPos(pos);
    } else {
        runner->setPos(0);
    }
    runner->setFirst(0);
    // считываем первое число из последовательности
    Runs::readIntFromRunnerPos(runner, *runner->getFirst(), true);
    // а потом ставим метку возможного окончания серии
    runner->setEor(runner->getEof());
}

void Runs::readIntFromRunnerPos(Runner *runner,
                                int &num,
                                bool posMove)
{
    // всевозможные проверки
    QFile *file = runner->getFile();
    if (file == nullptr)
        return;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    // считываем число с текущей позиции
    QTextStream stream(file);
    QString thisNum;
    if (stream.seek(runner->getPos())) {
        stream >> thisNum;
        if (posMove)
            runner->posMove(thisNum.length()+1);
    }
    // ставим метку у бегунка, конец ли это файла или нет и закрываем его
    runner->setEof(stream.atEnd());
    file->close();
    // записываем прочитанное число при успешном исходе
    // или просто забиваем число нулем при плохом исходе
    if (!runner->getEof()) {
        num = stoi(thisNum.toStdString());
    } else {
        num = 0;
    }
}

void Runs::writeIntToRunnerPos(Runner *runner,
                               int num,
                               bool posMove)
{
    // всевозможные проверки
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
        // смещаем позицию далее после записи в эту позицию
        if (posMove)
            runner->posMove(QString::number(num).length()+1);
    }
    // ставим метку у бегунка, конец ли это файла или нет и закрываем его
    runner->setEof(file->atEnd());
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

void Runs::selectRunsReceiver(int a[],
                              int d[],
                              int arrSize,
                              int &j,
                              int &level)
{
    int temp; // вспомогательная переменная
    if (d[j] < d[j+1]) {
        j++;
    } else {
        if (d[j] == 0) {
            level++;
            temp = a[0];
            for (int i = 0; i < arrSize-1; ++i) {
                d[i] = temp = a[i+1] - a[i];
                a[i] = temp + a[i+1];
            }
        }
        j = 0;
    }
    d[j]--;
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
