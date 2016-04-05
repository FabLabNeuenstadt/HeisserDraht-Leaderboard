#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    serialHandler = new SerialHandler();

    /*Match* tmpMatch = new Match();
    tmpMatch->setName("Mr. Brot");
    tmpMatch->setDuration(QTime::fromMSecsSinceStartOfDay(2712736));
    leaderboard.append(tmpMatch);*/

    view.rootContext()->setContextProperty("leaderboard", QVariant::fromValue(leaderboard));
    view.setSource(QUrl(QStringLiteral("qrc:/MainForm.qml")));
    view.show();

    serialHandler->open("/dev/ttyACM0");

    newMatch();
}

void MainController::connectNewMatch()
{
    connect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));
    connect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));
    connect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    connect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));

    connect(currMatch, SIGNAL(stopped()), this, SLOT(addMatchToLeaderboard()));
}

void MainController::disconnectOldMatch()
{
    /*disconnect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));
    disconnect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));
    disconnect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    disconnect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));*/

    serialHandler->disconnect(currMatch); // disconnect all serialHandler-Signals from currMatch-Slots

    currMatch->disconnect(); // disconnect all currMatch-Signals from all Slots
    //disconnect(currMatch, SIGNAL(stopped()), this, SLOT(addMatchToLeaderboard()));
}

void MainController::newMatch() {
    disconnectOldMatch();

    currMatch = new Match();
    view.rootContext()->setContextProperty("currMatch", currMatch);
    connectNewMatch();
}

void MainController::addMatchToLeaderboard()
{
    const int listSize = leaderboard.size();
    int idx = -1;
    for (int i = 0; i < listSize; ++i)
    {
        Match* myMatch = static_cast<Match*>(leaderboard.at(i));
        if(currMatch->duration() < myMatch->duration())
        {
            idx = i;
            break;
        }
    }
    if(idx < 0) {
        idx = listSize;
    }

    leaderboard.insert(idx, currMatch);
    //newMatch();

    view.rootContext()->setContextProperty("leaderboard", QVariant::fromValue(leaderboard));
}
