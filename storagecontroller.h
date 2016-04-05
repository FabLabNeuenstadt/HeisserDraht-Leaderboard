#ifndef STORAGECONTROLLER_H
#define STORAGECONTROLLER_H

#include <QObject>
#include <QtSql/QtSql>
#include "match.h"

class StorageController : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase db;

public:
    explicit StorageController(QObject *parent = 0);
    ~StorageController();

signals:

public slots:
    void createTables();
    void storeMatch(Match* match);
};

#endif // STORAGECONTROLLER_H
