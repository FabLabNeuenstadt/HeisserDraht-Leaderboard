#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQuickView>
#include <QQuickItem>
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
    QQuickView *dialogView;
    QList<QObject*> leaderboard;

    void connectNewMatch();
    void disconnectOldMatch();
    void newMatch();

public:
    explicit MainController(QObject *parent = 0);

signals:

public slots:
    void addMatchToLeaderboard(QString name, QTime duration, int mistakeCount);
};

#endif // MAINCONTROLLER_H
