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
    QQuickView *avatarView;
    StorageController *storageCtrl;
    QList<QObject*> leaderboard;

    void connectNewMatch();
    void disconnectOldMatch();
    void newMatch();

public:
    explicit MainController(QObject *parent = 0);

signals:
    void addEntry(QString name, int duration, int mistakeCount, int avatarId);

public slots:
    void addMatchToLeaderboard(QString name, int duration, int mistakeCount, int avatarId);
    void showDialog();
    void hideDialog();
    void showAvatarForm();
    void hideAvatarForm();
};

#endif // MAINCONTROLLER_H
