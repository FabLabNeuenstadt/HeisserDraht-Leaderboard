#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQuickView>
#include <QQmlContext>
#include <QList>
#include "serialhandler.h"
#include "match.h"

class MainController : public QObject
{
    Q_OBJECT
private:
    SerialHandler* serialHandler;
    Match* currMatch;
    QQuickView view;
    QList<QObject*> leaderboard;

    void connectNewMatch();
    void disconnectOldMatch();
    void newMatch();

public:
    explicit MainController(QObject *parent = 0);

signals:

public slots:
    void addMatchToLeaderboard();
};

#endif // MAINCONTROLLER_H
