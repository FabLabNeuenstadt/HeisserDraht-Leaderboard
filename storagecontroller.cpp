#include "storagecontroller.h"

StorageController::StorageController(QObject *parent) : QObject(parent)
{
    file = new QFile("data.csv");
    //file->open(QFile::ReadWrite);
}

void StorageController::read() {
    file->open(QFile::ReadOnly);

    QByteArray matchesData = file->readAll();
    QList<QByteArray> matches = matchesData.split('\n');
    QListIterator<QByteArray> matchIt(matches);
    while(matchIt.hasNext()) {
        QString line = QString(static_cast<QByteArray>(matchIt.next()));
        QList<QString> fields = line.split(';');

        if(fields.length() != 4) {
            continue;
        }

        QString name = fields.at(0);
        int duration = fields.at(1).toInt();
        int mistakeCount = fields.at(2).toInt();
        int avatarId = fields.at(3).toInt();

        emit addMatchToLeaderboard(name, duration, mistakeCount, avatarId);
    }

    matches.clear();
    file->close();
}

void StorageController::openForAppend()
{
    file->open(QFile::Append);
}

StorageController::~StorageController()
{
    file->close();
}

void StorageController::createTables()
{
}

void StorageController::storeMatch(Match *match)
{    
    QString line = QString("\n" +
            match->name() + ";" +
            QString::number(match->duration().msecsSinceStartOfDay()) + ";" +
            QString::number(match->mistakeCount()) + ";" +
            QString::number(match->avatarId()));
    file->write(line.toStdString().c_str());
    file->flush();
}
