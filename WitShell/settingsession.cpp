#include "settingsession.h"
#include "serialsessionattribute.h"

SettingSession::SettingSession(QObject *parent) : QObject(parent),
    m_settings(QSettings::IniFormat, QSettings::UserScope,
               "WitShell", "Sessions")
{
}

QList<SessionAttribute *> SettingSession::getSettingSessions()
{
    QList<SessionAttribute *> sessions;
    QStringList groups = m_settings.childGroups();
    foreach (const QString &group, groups) {
        m_settings.beginGroup(group);
        SessionAttribute::Protocol protocol = SessionAttribute::Protocol(m_settings.value("Protocol").toInt());
        switch (protocol) {
        case SessionAttribute::Serial:
        {
            SerialSessionAttribute *serialSession = new SerialSessionAttribute(this);
            serialSession->setName(group);
            serialSession->setPortName(m_settings.value("PortName").toString());
            serialSession->setHostName(m_settings.value("HostName").toString());
            serialSession->setBaudRate(m_settings.value("BaudRate").toInt());
            serialSession->setDataBit(QSerialPort::DataBits(m_settings.value("DataBit").toInt()));
            serialSession->setStopBit(QSerialPort::StopBits(m_settings.value("StopBit").toInt()));
            serialSession->setParity(QSerialPort::Parity(m_settings.value("Parity").toInt()));
            serialSession->setFlowControl(QSerialPort::FlowControl(m_settings.value("FlowControl").toInt()));
            sessions.append(serialSession);
        }
            break;
        default:
            break;
        }
        m_settings.endGroup();
    }

    return sessions;
}

void SettingSession::save(SessionAttribute *session)
{
    if(SerialSessionAttribute *serial =
            qobject_cast<SerialSessionAttribute *>(session)) {
        m_settings.beginGroup(serial->name());
        m_settings.setValue("PortName", serial->portName());
        m_settings.setValue("HostName", serial->hostName());
        m_settings.setValue("BaudRate", serial->baudRate());
        m_settings.setValue("DataBit", serial->dataBit());
        m_settings.setValue("StopBit", serial->stopBit());
        m_settings.setValue("Parity", serial->parity());
        m_settings.setValue("FlowControl", serial->flowControl());
        m_settings.endGroup();
    }
}

void SettingSession::remove(SessionAttribute *session)
{
    m_settings.remove(session->name());
}
