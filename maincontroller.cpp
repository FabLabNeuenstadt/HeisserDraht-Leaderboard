#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    serialHandler = new SerialHandler();

    /*Match* tmpMatch = new Match();
    tmpMatch->setName("Mr. Brot");
    tmpMatch->setDuration(QTime::fromMSecsSinceStartOfDay(2712736));
    leaderboard.append(tmpMatch);*/

    storageCtrl = new StorageController();

    view.rootContext()->setContextProperty("leaderboard", QVariant::fromValue(leaderboard));
    view.setSource(QUrl(QStringLiteral("qrc:/MainForm.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.showFullScreen();

    avatarView = new QQuickView();
    avatarView->setSource(QUrl(QStringLiteral("qrc:/chooseAvatarForm.qml")));
    avatarView->setResizeMode(QQuickView::SizeRootObjectToView);
    QObject* avatarRoot = dynamic_cast<QObject*>(avatarView->rootObject());

    dialogView = new QQuickView();
    dialogView->rootContext()->setContextProperty("avatarForm", avatarRoot);
    dialogView->setSource(QUrl(QStringLiteral("qrc:/NewEntryForm.qml")));
    QObject* dialogRoot = dynamic_cast<QObject*>(dialogView->rootObject());

    newMatch();

    connect(dialogRoot, SIGNAL(buttonAddClicked(QString, int, int, int)), this, SLOT(addMatchToLeaderboard(QString, int, int, int)));
    connect(dialogRoot, SIGNAL(buttonCancelClicked()), this, SLOT(hideDialog()));
    connect(dialogRoot, SIGNAL(chooseAvatarClicked()), this, SLOT(showAvatarForm()));

    connect(avatarRoot, SIGNAL(avatarChosen(int)), this, SLOT(hideAvatarForm()));

    connect(storageCtrl, SIGNAL(addMatchToLeaderboard(QString,int,int,int)), this, SLOT(addMatchToLeaderboard(QString,int,int,int)));

    storageCtrl->read();

    storageCtrl->openForAppend();

    serialHandler->open("/dev/ttyUSB0");

    //dialogView->show();
}

void MainController::connectNewMatch()
{
    // start
    connect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));

    // mistake
    connect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));

    // Stop
    connect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    connect(serialHandler, SIGNAL(stopped(QTime,int)), this, SLOT(showDialog()));

    connect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));

    //connect(currMatch, SIGNAL(stopped()), this, SLOT(addMatchToLeaderboard()));
    //connect(currMatch, SIGNAL(stopped(int, int)), dynamic_cast<QObject*>(dialogView->rootObject()), SLOT(display(int, int)));
    //connect(currMatch, SIGNAL(stopped()), dialogView, SLOT(show()));
}

void MainController::disconnectOldMatch()
{
    /*disconnect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));
    disconnect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));
    disconnect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    disconnect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));*/

    serialHandler->disconnect(currMatch); // disconnect all serialHandler-Signals from currMatch-Slots

    currMatch->disconnect(); // disconnect all currMatch-Signals from all Slots
    //connect(currMatch, SIGNAL(stopped(int,int)), dialogView, SLOT(show()));
    //disconnect(currMatch, SIGNAL(stopped()), this, SLOT(addMatchToLeaderboard()));
}

void MainController::newMatch() {
    //disconnectOldMatch();

    currMatch = new Match();
    view.rootContext()->setContextProperty("currMatch", currMatch);
    dialogView->rootContext()->setContextProperty("currMatch", currMatch);
    connectNewMatch();
}

void MainController::addMatchToLeaderboard(QString name, int duration, int mistakeCount, int avatarId)
{
    Match* currMatch = new Match();
    currMatch->setName(name);
    currMatch->setDuration(QTime::fromMSecsSinceStartOfDay(duration));
    currMatch->setMistakeCount(mistakeCount);
    currMatch->setAvatarId(avatarId);

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
    storageCtrl->storeMatch(currMatch);

    dialogView->hide();
}

void MainController::showDialog()
{
    dialogView->show();
}

void MainController::hideDialog()
{
    dialogView->hide();
}

void MainController::showAvatarForm()
{
    avatarView->show();
}

void MainController::hideAvatarForm()
{
    avatarView->hide();
}

