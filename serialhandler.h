#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QTime>
#include <QtSerialPort/QSerialPort>

class SerialHandler : public QObject
{
    Q_OBJECT

private:
    QSerialPort* serial;

public:
    SerialHandler();
    void open(QString name);

signals:
    void started(QTime penaltyTime);
    void stopped(QTime time, int hitCount);
    void reset();
    void mistake(QTime time, int hitCount);
    void timeChanged(QTime time);

public slots:
    void read();
};

#endif // SERIALHANDLER_H
