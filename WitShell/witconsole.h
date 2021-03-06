#ifndef WITCONSOLE_H
#define WITCONSOLE_H

#include <QMainWindow>
#include "allsessiondialog.h"
#include "newsessiondialog.h"
#include "consoletextedit.h"


namespace Ui {
class WitConsole;
}

class WitConsole : public QMainWindow
{
    Q_OBJECT

public:
    explicit WitConsole(QWidget *parent = 0);
    ~WitConsole();

public slots:
    void onConnectSession(int index);

protected:
    void connectSession(SessionAttribute *session);
    void disconnectSession();

    void enableConnectButton(bool conn);

private slots:
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

    void on_act_session_triggered();
    void on_act_attribute_triggered();

    void on_act_font_triggered();

    void on_act_connect_triggered();

    void on_act_disconnect_triggered();

    void on_act_find_triggered();

    void on_act_fullscreen_triggered();

private:
    Ui::WitConsole *ui;
    AllSessionDialog *allsession;
    SessionAttribute *currentSession;
    QSerialPort *m_serial;
    ConsoleTextEdit *m_console;
};

#endif // WITCONSOLE_H
