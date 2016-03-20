#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQuickView>
#include <QQmlContext>
#include "serialhandler.h"
#include "match.h"

class MainController : public QObject
{
    Q_OBJECT
private:
    SerialHandler* serialHandler;
    Match* currMatch;
    QQuickView view;

public:
    explicit MainController(QObject *parent = 0);

signals:

public slots:
};

#endif // MAINCONTROLLER_H
