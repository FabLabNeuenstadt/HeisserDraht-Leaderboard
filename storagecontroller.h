#ifndef STORAGECONTROLLER_H
#define STORAGECONTROLLER_H

#include <QObject>
#include <QFile>
#include "match.h"

class StorageController : public QObject
{
    Q_OBJECT
private:
    QFile *file;

public:
    explicit StorageController(QObject *parent = 0);
    ~StorageController();

signals:
    void addMatchToLeaderboard(QString name, int duration, int mistakeCount, int avatarId);

public slots:
    void createTables();
    void storeMatch(Match* match);
    void read();
    void openForAppend();
};

#endif // STORAGECONTROLLER_H
