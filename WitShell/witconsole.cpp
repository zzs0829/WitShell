#include "witconsole.h"
#include "ui_witconsole.h"

WitConsole::WitConsole(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WitConsole),
    allsession(new AllSessionDialog(this))
{
    ui->setupUi(this);
}

WitConsole::~WitConsole()
{
    delete ui;
}

/**
 * @brief 点击【工具栏-会话】按钮，打开会话对话框
 */
void WitConsole::on_act_session_triggered()
{
    allsession->show();
}

/**
 * @brief 点击【工具栏-属性】按钮，打开当前会话的属性对话框
 */
void WitConsole::on_act_attribute_triggered()
{
}
