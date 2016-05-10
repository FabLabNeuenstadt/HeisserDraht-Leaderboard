#include "match.h"

QTime Match::duration() const
{
    return _duration;
}

void Match::setDuration(QTime duration)
{
    _duration = duration;
    setDurationStr(_duration.toString("mm:ss.zzz"));
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

int Match::avatarId() const
{
    return _avatarId;
}

void Match::setAvatarId(int avatarId)
{
    _avatarId = avatarId;
}

void Match::setDurationStr(const QString &durationStr)
{
    _durationStr = durationStr;
}

Match::Match(QObject *parent) : QObject(parent)
{
    updateTimer = new QTimer();
    updateTimer->setInterval(10);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    setDuration(QTime::fromMSecsSinceStartOfDay(0));
    setMistakeCount( 0);
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
    setPenaltyTime( penaltyTime);

    updateTimer->start();
}

void Match::mistake(QTime duration, int mistakeCount)
{
    setMistakeCount(mistakeCount);
    setDuration(duration);
}

void Match::stop(QTime duration, int mistakeCount)
{
    updateTimer->stop();

    // use the time, that was meassured by the arduino
    setDuration(duration);
    setMistakeCount(mistakeCount);

    emit stopped(duration.msecsSinceStartOfDay(), mistakeCount);
}

void Match::update()
{
    int currPenaltyTime = mistakeCount() * penaltyTime().msecsSinceStartOfDay();
    setDuration(QTime::fromMSecsSinceStartOfDay(startTime.msecsTo(QTime::currentTime()) + currPenaltyTime));
}
