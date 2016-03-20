#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainController* mainController = new MainController();

    return app.exec();
}
