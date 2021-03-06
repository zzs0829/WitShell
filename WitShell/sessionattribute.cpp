#include "sessionattribute.h"
#include <QUuid>

SessionAttribute::SessionAttribute(Protocol protocol, QObject *parent) : QObject(parent)
  ,m_protocol(protocol)
  ,m_reconnect(false)
  ,m_reconnectInterval(0)
  ,m_reconnectLimit(0)
{
    m_uuid = QUuid::createUuid().toString();
}
