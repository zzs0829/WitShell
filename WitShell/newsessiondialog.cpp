#include "newsessiondialog.h"
#include "ui_newsessiondialog.h"
#include <QSerialPortInfo>
#include <QDebug>
#include "serialsessionattribute.h"

NewSessionDialog::NewSessionDialog(SessionAttribute *attribute, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSessionDialog),
    m_attribute(attribute)
{
    ui->setupUi(this);

    dataArray << QSerialPort::Data5
              << QSerialPort::Data6
              << QSerialPort::Data7
              << QSerialPort::Data8;


    stopArray << QSerialPort::OneStop
              << QSerialPort::OneAndHalfStop
              << QSerialPort::TwoStop;

    parityArray << QSerialPort::NoParity
                << QSerialPort::EvenParity
                << QSerialPort::OddParity
                << QSerialPort::SpaceParity
                << QSerialPort::MarkParity;

    flowArray << QSerialPort::NoFlowControl
              << QSerialPort::HardwareControl
              << QSerialPort::SoftwareControl;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->cbx_port->addItem(info.portName());
    }

    const auto bauds = QSerialPortInfo::standardBaudRates();
    for (const qint32 &baud : bauds) {
        ui->cbx_baud->addItem(QString::number(baud));
    }

    if(SerialSessionAttribute *serial =
            qobject_cast<SerialSessionAttribute *>(m_attribute)) {
        ui->txt_name->setText(serial->name());
        ui->cbx_port->setCurrentText(serial->portName());
        ui->cbx_baud->setCurrentText(QString::number(serial->baudRate()));
        ui->cbx_data->setCurrentIndex(dataArray.indexOf(serial->dataBit()));
        ui->cbx_stop->setCurrentIndex(stopArray.indexOf(serial->stopBit()));
        ui->cbx_parity->setCurrentIndex(parityArray.indexOf(serial->parity()));
        ui->cbx_flow->setCurrentIndex(flowArray.indexOf(serial->flowControl()));
    }
}

NewSessionDialog::~NewSessionDialog()
{
    delete ui;
}

/**
 * @brief 点击【确定】按钮，保存当前的会话属性。
 */
void NewSessionDialog::on_btn_submit_clicked()
{
    if(SerialSessionAttribute *serial =
            qobject_cast<SerialSessionAttribute *>(m_attribute)) {
        serial->setName(ui->txt_name->text());
        serial->setportName(ui->cbx_port->currentText());
        serial->setBaudRate(ui->cbx_baud->currentText().toInt());
        serial->setDataBit(dataArray[ui->cbx_data->currentIndex()]);
        serial->setStopBit(stopArray[ui->cbx_stop->currentIndex()]);
        serial->setParity(parityArray[ui->cbx_parity->currentIndex()]);
        serial->setFlowControl(flowArray[ui->cbx_flow->currentIndex()]);
    }
}

/**
 * @brief 点击【取消】按钮，放弃保存当前的会话属性。
 */
void NewSessionDialog::on_btn_cancel_clicked()
{
    this->reject();
}
