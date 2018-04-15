#ifndef WITCONSOLE_H
#define WITCONSOLE_H

#include <QMainWindow>
#include "allsessiondialog.h"
#include "newsessiondialog.h"


namespace Ui {
class WitConsole;
}

class WitConsole : public QMainWindow
{
    Q_OBJECT

public:
    explicit WitConsole(QWidget *parent = 0);
    ~WitConsole();

private slots:
    void on_act_session_triggered();
    void on_act_attribute_triggered();

private:
    Ui::WitConsole *ui;
    AllSessionDialog *allsession;
};

#endif // WITCONSOLE_H
