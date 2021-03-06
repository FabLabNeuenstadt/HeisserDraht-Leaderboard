#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QString>

class Match : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QTime duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QString durationStr READ durationStr NOTIFY durationChanged)
    Q_PROPERTY(int mistakeCount READ mistakeCount WRITE setMistakeCount NOTIFY mistakeCountChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int avatarId READ avatarId WRITE setAvatarId NOTIFY avatarIdChanged)

private:
    QTimer* updateTimer;

    QTime startTime;

    QTime _duration;
    QString _durationStr;
    int _mistakeCount;

    QTime _penaltyTime;

    QString _name;

    int _avatarId;

    void setDurationStr(const QString &durationStr);

public:
    explicit Match(QObject *parent = 0);
    ~Match();

    QTime duration() const;
    void setDuration(QTime duration);

    int mistakeCount() const;
    void setMistakeCount(int mistakeCount);

    QString durationStr() const;

    QString name() const;
    void setName(const QString &name);

    QTime penaltyTime() const;
    void setPenaltyTime(const QTime &penaltyTime);

    int avatarId() const;
    void setAvatarId(int avatarId);

signals:
    void durationChanged();
    void mistakeCountChanged();
    void nameChanged();
    void stopped(int duration, int mistakeCount);
    void avatarIdChanged();

public slots:
    void start(QTime penaltyTime);
    void stop(QTime duration, int mistakeCount);
    void mistake(QTime duration, int mistakeCount);
    void update();
};

#endif // MATCH_H
