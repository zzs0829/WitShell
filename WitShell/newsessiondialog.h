#ifndef NEWSESSIONDIALOG_H
#define NEWSESSIONDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include "sessionattribute.h"

namespace Ui {
class NewSessionDialog;
}

class NewSessionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewSessionDialog(SessionAttribute *attribute, QWidget *parent = 0);
    ~NewSessionDialog();

private slots:
    void on_btn_submit_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::NewSessionDialog *ui;

    QList<QSerialPort::DataBits> dataArray;
    QList<QSerialPort::StopBits> stopArray;
    QList<QSerialPort::Parity> parityArray;
    QList<QSerialPort::FlowControl> flowArray;

    SessionAttribute *m_attribute;
};

#endif // NEWSESSIONDIALOG_H
