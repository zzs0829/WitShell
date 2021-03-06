#ifndef SETTINGSESSION_H
#define SETTINGSESSION_H

#include <QObject>
#include <QSettings>
#include "sessionattribute.h"

class SettingSession : public QObject
{
    Q_OBJECT
public:
    explicit SettingSession(QObject *parent = 0);

    QList<SessionAttribute *> getSettingSessions();

    void save(SessionAttribute *session);
    void remove(SessionAttribute *session);

signals:

public slots:

private:
    QSettings m_settings;
};

#endif // SETTINGSESSION_H
