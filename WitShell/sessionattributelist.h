#ifndef SESSIONATTRIBUTELIST_H
#define SESSIONATTRIBUTELIST_H

#include <QObject>
#include "sessionattribute.h"

class SessionAttributeList : public QObject
{
    Q_OBJECT
public:
    explicit SessionAttributeList(QObject *parent = 0);

signals:

public slots:

private:
    QList<SessionAttribute *> m_sessions;
};

#endif // SESSIONATTRIBUTELIST_H
