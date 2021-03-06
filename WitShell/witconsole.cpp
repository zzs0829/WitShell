#include "witconsole.h"
#include "ui_witconsole.h"
#include "serialsessionattribute.h"
#include <QFontDialog>
#include <QMessageBox>
#include <QDebug>

WitConsole::WitConsole(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WitConsole),
    allsession(new AllSessionDialog(this)),
    currentSession(Q_NULLPTR)
{
    ui->setupUi(this);
    connect(allsession, SIGNAL(connectSession(int)), SLOT(onConnectSession(int)));

    m_console = new ConsoleTextEdit(this);
    this->setCentralWidget(m_console);

    m_serial = new QSerialPort(this);
    connect(m_serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &WitConsole::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &WitConsole::readData);
    connect(m_console, &ConsoleTextEdit::getData, this, &WitConsole::writeData);
}

WitConsole::~WitConsole()
{
    delete ui;

    this->disconnectSession();
}

void WitConsole::writeData(const QByteArray &data)
{
    if(m_serial->isWritable())
        m_serial->write(data);
}

void WitConsole::readData()
{
    QByteArray data = m_serial->readAll();
    qDebug() << "READ: " << data;
    m_console->putData(data);
}

void WitConsole::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("串口错误"), m_serial->errorString());
        //        closeSerialPort();
        if (m_serial->isOpen())
            m_serial->close();
    }
}

void WitConsole::onConnectSession(int index)
{
    currentSession = allsession->getSessions(index);
    this->connectSession(currentSession);
}

// 连接串口
void WitConsole::connectSession(SessionAttribute *session)
{
    if(SerialSessionAttribute *attribute =
            qobject_cast<SerialSessionAttribute *>(session)) {
        m_serial->setPortName(attribute->portName());
        m_serial->setBaudRate(attribute->baudRate());
        m_serial->setDataBits(attribute->dataBit());
        m_serial->setParity(attribute->parity());
        m_serial->setStopBits(attribute->stopBit());
        m_serial->setFlowControl(attribute->flowControl());
        if (m_serial->open(QIODevice::ReadWrite)) {
            m_console->setEnabled(true);
            this->enableConnectButton(true);
        } else {
            QMessageBox::critical(this, tr("Error"), m_serial->errorString());
        }
    }else{
        qWarning() << "The current session is null.";
    }
}

// 断开连接，关闭串口
void WitConsole::disconnectSession()
{
    if (m_serial->isOpen())
        m_serial->close();
    this->enableConnectButton(false);
}

// 根据连接状态设置按钮【连接/断开】是否可用
void WitConsole::enableConnectButton(bool conn)
{
    if(currentSession) {
        ui->act_connect->setEnabled(!conn);
        ui->act_disconnect->setEnabled(conn);
    }else{
        ui->act_connect->setEnabled(false);
        ui->act_disconnect->setEnabled(false);
    }
}

// 点击【工具栏-会话】按钮，打开会话对话框
void WitConsole::on_act_session_triggered()
{
    allsession->show();
}

// 点击【工具栏-属性】按钮，打开当前会话的属性对话框
void WitConsole::on_act_attribute_triggered()
{
}

// 点击【工具栏-连接】按钮，连接终端
void WitConsole::on_act_connect_triggered()
{
    this->connectSession(currentSession);
}

// 点击【工具栏-断开】按钮，断开连接
void WitConsole::on_act_disconnect_triggered()
{
    this->disconnectSession();
}

// 点击【工具栏-字体】按钮，打开当前会话的字体对话框
void WitConsole::on_act_font_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(
                &ok, m_console->font(), this);
    if (ok) {
        m_console->setFont(font);
    }
}

// 点击【工具栏-查找】按钮，打开当前会话的查找对话框
void WitConsole::on_act_find_triggered()
{

}

// 点击【工具栏-全屏】按钮，进入/退出全屏模式
void WitConsole::on_act_fullscreen_triggered()
{
    if(this->isFullScreen())
        this->showNormal();
    else
        this->showFullScreen();
}
