#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QList>
#include "serialhandler.h"
#include "match.h"
#include "storagecontroller.h"

class MainController : public QObject
{
    Q_OBJECT
private:
    SerialHandler* serialHandler;
    Match* currMatch;
    QQuickView view;
    QQuickView *dialogView;
    StorageController *storageCtrl;
    QList<QObject*> leaderboard;

    void connectNewMatch();
    void disconnectOldMatch();
    void newMatch();

public:
    explicit MainController(QObject *parent = 0);

signals:

public slots:
    void addMatchToLeaderboard(QString name, int duration, int mistakeCount);
    void showDialog();
    void hideDialog();
};

#endif // MAINCONTROLLER_H
