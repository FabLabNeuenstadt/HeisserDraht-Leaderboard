#include "serialhandler.h"

SerialHandler::SerialHandler()
{
    serial = new QSerialPort();

    connect(serial, SIGNAL(readyRead()), this, SLOT(read()));
}

void SerialHandler::open(QString name)
{
    serial->setPortName(name);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadOnly)) {
        return;
    } else { // TODO: error-handling
        return;
    }
}

void SerialHandler::read()
{
    QByteArray data = serial->readLine();
    QString dataStr = QString(data);

    dataStr = dataStr.remove('\r');
    dataStr = dataStr.remove('\n');

    QTime time;
    int hitCount;
    QString status;
    try {
        QStringList params = dataStr.split(';');
        time = QTime::fromString(params[0],"mm:ss.zzz");
        hitCount = params[1].toInt();
        status = params[2];
    } catch(...)
    {
        // ToDo: Error-Handling
    }

    if(status == "Start")
    {
        emit started(time);
    }
    else if(status == "Reset")
    {
        emit reset();
    }
    else if(status == "Mistake")
    {
        emit mistake(time, hitCount);
    }
    else if(status == "Stop")
    {
        emit stopped(time, hitCount);
    }
}
