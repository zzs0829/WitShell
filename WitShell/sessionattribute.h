#ifndef SESSIONATTRIBUTE_H
#define SESSIONATTRIBUTE_H

#include <QObject>

class SessionAttribute : public QObject
{
    Q_OBJECT
public:
    enum Protocol {
        Serial
    };

    QString uuid() const { return m_uuid; }

    QString name() const { return m_name; }
    void setName(const QString &name) {
        if(name != m_name) {
            m_name = name;
            emit nameChanged();
        }
    }

    QString portName() const { return m_portName; }
    void setPortName(const QString &portName) {
        if(portName != m_portName) {
            m_portName = portName;
            emit portNameChanged();
        }
    }

    Protocol protocol() const { return m_protocol; }
    void setProtocol(Protocol protocol) {
        if(protocol != m_protocol) {
            m_protocol = protocol;
            emit protocolChanged();
        }
    }

    QString hostName() const { return m_hostName; }
    void setHostName(const QString &hostName) {
        if(hostName != m_hostName) {
            m_hostName = hostName;
            emit hostNameChanged();
        }
    }

    bool reconnect() const { return m_reconnect; }
    void setReconnect(bool reconnect) {
        if(reconnect != m_reconnect) {
            m_reconnect = reconnect;
            emit reconnectChanged();
        }
    }

    quint32 reconnectInterval() const { return m_reconnectInterval; }
    void setReconnectInterval(quint32 reconnectInterval) {
        if(reconnectInterval != m_reconnectInterval) {
            m_reconnectInterval = reconnectInterval;
            emit reconnectIntervalChanged();
        }
    }

    quint32 reconnectLimit() const { return m_reconnectLimit; }
    void setReconnectLimit(quint32 reconnectLimit) {
        if(reconnectLimit != m_reconnectLimit) {
            m_reconnectLimit = reconnectLimit;
            emit reconnectLimitChanged();
        }
    }

    static QString toString(Protocol protocol, bool full = false) {
        QString shortStr = "";
        switch (protocol) {
        case Serial:
            shortStr = "Serial";
            break;
        default:
            shortStr = QString::number(protocol);
            break;
        }
        if(full)
            return QString("SessionAttribute::%1").arg(shortStr);
        else
            return shortStr;
    }

Q_SIGNALS:
    void nameChanged();
    void portNameChanged();
    void protocolChanged();
    void hostNameChanged();
    void reconnectChanged();
    void reconnectIntervalChanged();
    void reconnectLimitChanged();

protected:
    explicit SessionAttribute(Protocol protocol, QObject *parent = nullptr);

private:
    QString m_uuid;
    QString m_name;
    QString m_portName;
    Protocol m_protocol;
    QString m_hostName;
    bool m_reconnect;
    quint32 m_reconnectInterval; // second
    quint32 m_reconnectLimit; // miniute
};

#endif // SESSIONATTRIBUTE_H
