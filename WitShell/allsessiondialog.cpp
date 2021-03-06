#include "allsessiondialog.h"
#include "ui_allsessiondialog.h"
#include "newsessiondialog.h"
#include "serialsessionattribute.h"
#include <QDebug>

#define COLUMN_NAME     0
#define COLUMN_HOST     1
#define COLUMN_PORT     2
#define COLUMN_PROTOCOL 3

AllSessionDialog::AllSessionDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllSessionDialog),
    m_setting(new SettingSession(this))
{
    ui->setupUi(this);
    m_sessions = m_setting->getSettingSessions();
    foreach (SessionAttribute *session, m_sessions) {
        appendSessionTable(session);
    }
}

AllSessionDialog::~AllSessionDialog()
{
    delete ui;
}

SessionAttribute *AllSessionDialog::getSessions(int index)
{
    return m_sessions.at(index);
}

QString AllSessionDialog::newSessionName() const
{
    QString templName= tr("新建会话");
    QRegExp rx(QString("^%1[(](\\d+)[)]$").arg(templName));

    int index = -1;
    foreach (const SessionAttribute *session, m_sessions) {
        int pos = rx.indexIn(session->name());
        if(pos == 0) {
            int num = rx.cap(1).toInt();
            index = qMax(index, num);
        }else if(session->name() == templName) {
            index = qMax(index, 0);
        }
    }
    // Next Session
    index++;
    if(index == 0)
        return templName;
    else
        return QString("%1(%2)").arg(templName).arg(index);
}

SessionAttribute *AllSessionDialog::createSerialSession()
{
    SerialSessionAttribute *serialSession = new SerialSessionAttribute(this);
    serialSession->setName(newSessionName());
    serialSession->setHostName("localhost");
    serialSession->setBaudRate(115200);
    serialSession->setDataBit(QSerialPort::Data8);
    serialSession->setStopBit(QSerialPort::OneStop);
    serialSession->setParity(QSerialPort::NoParity);
    serialSession->setFlowControl(QSerialPort::NoFlowControl);

    return serialSession;
}

void AllSessionDialog::appendSession(SessionAttribute *session)
{
    m_sessions.append(session);
    appendSessionTable(session);
    m_setting->save(session);
}

void AllSessionDialog::appendSessionTable(SessionAttribute *session)
{
    int newline = ui->tbl_sessions->rowCount();
    ui->tbl_sessions->insertRow(newline);
    ui->tbl_sessions->setItem(newline, COLUMN_NAME, new QTableWidgetItem(session->name()));
    ui->tbl_sessions->setItem(newline, COLUMN_HOST, new QTableWidgetItem(session->hostName()));
    ui->tbl_sessions->setItem(newline, COLUMN_PORT, new QTableWidgetItem(session->portName()));
    QString protocolStr = SessionAttribute::toString(session->protocol());
    ui->tbl_sessions->setItem(newline, COLUMN_PROTOCOL, new QTableWidgetItem(protocolStr));
}

void AllSessionDialog::on_act_create_triggered()
{
    SessionAttribute *newSession = createSerialSession();
    NewSessionDialog *newDialog = new NewSessionDialog(newSession, this);
    newDialog->setAttribute(Qt::WA_DeleteOnClose);
    int result = newDialog->exec();
    switch (result) {
    case QDialog::Accepted:
        appendSession(newSession);
        break;
    case QDialog::Rejected:
        newSession->deleteLater();
        break;
    default:
        break;
    }
}

void AllSessionDialog::on_act_attribute_triggered()
{

}

// 点击【连接】按钮
void AllSessionDialog::on_btn_connect_clicked()
{
    if(QTableWidgetItem* item = ui->tbl_sessions->selectedItems().first()) {
        emit connectSession(item->row());
        this->close();
    }
}

// 点击【关闭】按钮
void AllSessionDialog::on_btn_close_clicked()
{
    this->close();
}

// 选择会话后方可启用【连接】按钮
void AllSessionDialog::on_tbl_sessions_itemSelectionChanged()
{
    if(ui->tbl_sessions->selectedItems().count() > 0)
        ui->btn_connect->setEnabled(true);
    else
        ui->btn_connect->setEnabled(false);
}

// 双击会话列表
void AllSessionDialog::on_tbl_sessions_doubleClicked(const QModelIndex &index)
{
    emit connectSession(index.row());
    this->close();
}
