#include "match.h"

QTime Match::duration() const
{
    return _duration;
}

void Match::setDuration(QTime duration)
{
    _duration = duration;
    setDurationStr(duration.toString("mm:ss.zzz"));
    emit durationChanged();
}

int Match::mistakeCount() const
{
    return _mistakeCount;
}

void Match::setMistakeCount(int mistakeCount)
{
    _mistakeCount = mistakeCount;
    emit mistakeCountChanged();
}

QString Match::durationStr() const
{
    return _durationStr;
}

QString Match::name() const
{
    return _name;
}

void Match::setName(const QString &name)
{
    _name = name;
    emit nameChanged();
}

QTime Match::penaltyTime() const
{
    return _penaltyTime;
}

void Match::setPenaltyTime(const QTime &penaltyTime)
{
    _penaltyTime = penaltyTime;
}

void Match::setDurationStr(const QString &durationStr)
{
    _durationStr = durationStr;
}

Match::Match(QObject *parent) : QObject(parent)
{
    setDuration(QTime::fromMSecsSinceStartOfDay(0));
    updateTimer = NULL;
}

Match::~Match()
{
    if(updateTimer) {
        delete updateTimer;
    }
}

void Match::start(QTime penaltyTime)
{
    startTime = QTime::currentTime();
    setPenaltyTime(penaltyTime);

    if(updateTimer == NULL) {
        updateTimer = new QTimer();
        updateTimer->setInterval(10);
        connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    }

    updateTimer->start();
}

void Match::mistake(QTime duration, int mistakeCount)
{
    setMistakeCount(mistakeCount);
    setDuration(duration);
}

void Match::stop(QTime duration, int mistakeCount)
{
    if(updateTimer) {
        updateTimer->stop();
        delete updateTimer;
        updateTimer = NULL;
    }

    // use the time, that was meassured by the arduino
    setDuration(duration);
    setMistakeCount(mistakeCount);

    emit stopped();
}

void Match::update()
{
    setDuration(QTime::fromMSecsSinceStartOfDay(startTime.msecsTo(QTime::currentTime())));
    updateTimer->start();
}


