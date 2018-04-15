#include "sessionattribute.h"
#include <QUuid>

SessionAttribute::SessionAttribute(QObject *parent) : QObject(parent)
  ,m_protocol(SessionAttribute::Serial)
  ,m_reconnect(false)
  ,m_reconnectInterval(0)
  ,m_reconnectLimit(0)
{
    m_uuid = QUuid::createUuid().toString();
}
