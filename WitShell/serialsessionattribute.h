#ifndef SERIALSESSIONATTRIBUTE_H
#define SERIALSESSIONATTRIBUTE_H

#include "sessionattribute.h"
#include <QSerialPort>

class SerialSessionAttribute : public SessionAttribute
{
    Q_OBJECT
public:
    explicit SerialSessionAttribute(QObject *parent = nullptr);

    QString portName() const { return m_portName; }
    void setportName(const QString &portName) {
        if(portName != m_portName) {
            m_portName = portName;
            emit portNameChanged();
        }
    }

    qint32 baudRate() const { return m_baudRate; }
    void setBaudRate(qint32 rate) {
        if(rate != m_baudRate) {
            m_baudRate = rate;
            emit baudRateChanged();
        }
    }

    QSerialPort::DataBits dataBit() const { return m_dataBit; }
    void setDataBit(QSerialPort::DataBits bit) {
        if(bit != m_dataBit) {
            m_dataBit = bit;
            emit dataBitChanged();
        }
    }

    QSerialPort::StopBits stopBit() const { return m_stopBit; }
    void setStopBit(QSerialPort::StopBits bit) {
        if(bit != m_stopBit) {
            m_stopBit = bit;
            emit stopBitChanged();
        }
    }

    QSerialPort::Parity parity() const { return m_parity; }
    void setParity(QSerialPort::Parity parity) {
        if(parity != m_parity) {
            m_parity = parity;
            emit parityChanged();
        }
    }

    QSerialPort::FlowControl flowControl() const { return m_flowControl; }
    void setFlowControl(QSerialPort::FlowControl flow) {
        if(flow != m_flowControl) {
            m_flowControl = flow;
            emit flowControlChanged();
        }
    }

Q_SIGNALS:
    void portNameChanged();
    void baudRateChanged();
    void dataBitChanged();
    void stopBitChanged();
    void parityChanged();
    void flowControlChanged();

private:
    QString m_portName;
    qint32 m_baudRate;
    QSerialPort::DataBits m_dataBit;
    QSerialPort::StopBits m_stopBit;
    QSerialPort::Parity m_parity;
    QSerialPort::FlowControl m_flowControl;
};

#endif // SERIALSESSIONATTRIBUTE_H
