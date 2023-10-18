#include "runs.h"

void Runs::openRandomSeq(QString path,
                         QString name,
                         int lenght)
{
    QString filePath = path + '/' + name;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly  | QIODevice::Text))
        return;
    // если все успешно, можем писать случайную информацию в файл
    QTextStream out(&file);
    for (int i = 0; i < lenght-1; ++i) {
        int randNumber = QRandomGenerator::global()->bounded(669);
        out << randNumber << ' ';
    }
}

Runs::Runs()
{
}
