#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);

    serialHandler = new SerialHandler();

    storageCtrl = new StorageController();

    view.rootContext()->setContextProperty("mainCtrl", this);
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

    serialHandler->open(settings->value("port", "/dev/ttyUSB0").toString());
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
}

void MainController::disconnectOldMatch()
{
    serialHandler->disconnect(currMatch); // disconnect all serialHandler-Signals from currMatch-Slots

    currMatch->disconnect(); // disconnect all currMatch-Signals from all Slots
}

void MainController::newMatch() {
    currMatch = new Match();
    view.rootContext()->setContextProperty("currMatch", currMatch);
    dialogView->rootContext()->setContextProperty("currMatch", currMatch);
    connectNewMatch();
}

void MainController::addMatchToLeaderboard(QString name, int duration, int mistakeCount, int avatarId)
{
    emit addEntry(name, duration, mistakeCount, avatarId);

    Match* myMatch = new Match();
    myMatch->setName(name);
    myMatch->setDuration(QTime::fromMSecsSinceStartOfDay(duration));
    myMatch->setMistakeCount(mistakeCount);
    myMatch->setAvatarId(avatarId);
    storageCtrl->storeMatch(myMatch);

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

