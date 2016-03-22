#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    serialHandler = new SerialHandler();

    view.rootContext()->setContextProperty("leaderboard", QVariant::fromValue(leaderboard));
    view.setSource(QUrl(QStringLiteral("qrc:/MainForm.qml")));
    view.show();    

    serialHandler->open("/dev/ttyUSB0");

    newMatch();
}

void MainController::connectNewMatch()
{
    connect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));
    connect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));
    connect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    //connect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));

    connect(currMatch, SIGNAL(stopped()), this, SLOT(addMatchToLeaderboard()));
}

void MainController::disconnectOldMatch()
{
    disconnect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));
    disconnect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));
    disconnect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    //disconnect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));

    disconnect(currMatch, SIGNAL(stopped()), this, SLOT(addMatchToLeaderboard()));
}

void MainController::newMatch() {
    disconnectOldMatch();

    currMatch = new Match();
    view.rootContext()->setContextProperty("currMatch", currMatch);
    connectNewMatch();
}

void MainController::addMatchToLeaderboard()
{
    leaderboard.append(currMatch);
}
