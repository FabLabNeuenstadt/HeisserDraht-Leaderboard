#include "storagecontroller.h"

StorageController::StorageController(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    db.open();
}

StorageController::~StorageController()
{
    db.close();
}

void StorageController::createTables()
{
    {
        QSqlQuery query;
        query.prepare("CREATE TABLE matches (id INTEGER PRIMARY KEY, name VARCHAR(50), duration INTEGER, mistakeCount INTEGER, avatarId INTEGER");
        if(query.exec()) {

        }
    }
    {
        QSqlQuery query;
        query.prepare("CREATE INDEX durationIndex ON matches (duration)");
        if(query.exec()) {

        }
    }
}

void StorageController::storeMatch(Match *match)
{
    QSqlQuery query;
    query.prepare("INSERT INTO matches (name, duration, mistakeCount, avatarId) VALUES (:name, :duration, :mistakeCount, :avatarId)");
    query.bindValue(":name", QVariant(match->name()));
    query.bindValue(":duration", QVariant(match->duration()));
    query.bindValue(":mistakeCount", QVariant(match->mistakeCount()));
    query.bindValue(":avatarId", QVariant(match->avatarId()));
    if(query.exec()) {

    }
}
