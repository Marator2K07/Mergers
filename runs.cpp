#include "runs.h"

Runs::openRandomSeq(QString path,
                    QString name,
                    int lenght,
                    int seed)
{
    QString filePath = path + '/' + name;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
}

Runs::Runs()
{
}
