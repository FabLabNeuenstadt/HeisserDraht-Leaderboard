#include "storagecontroller.h"

StorageController::StorageController(QObject *parent) : QObject(parent)
{
    file = new QFile("data.csv");
    //file->open(QFile::ReadWrite);
}

QList<QObject*> StorageController::read() {
    //file->read()
}

void StorageController::openForAppend() {
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
            match->durationStr() + ";" +
            QString::number(match->mistakeCount()) + ";" +
            QString::number(match->avatarId()));
    file->write(line.toStdString().c_str());
    file->flush();
}
