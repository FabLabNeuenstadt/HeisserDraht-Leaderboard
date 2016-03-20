#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    currMatch = new Match();
    serialHandler = new SerialHandler();

    view.rootContext()->setContextProperty("currMatch", currMatch);
    view.setSource(QUrl(QStringLiteral("qrc:/MainForm.qml")));
    view.show();

    connect(serialHandler, SIGNAL(started(QTime)), currMatch, SLOT(start(QTime)));
    connect(serialHandler, SIGNAL(mistake(QTime,int)), currMatch, SLOT(mistake(QTime,int)));
    connect(serialHandler, SIGNAL(stopped(QTime,int)), currMatch, SLOT(stop(QTime,int)));
    //connect(serialHandler, SIGNAL(reset()), currMatch, SLOT(reset()));

    serialHandler->open("/dev/ttyUSB0");
}
