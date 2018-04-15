#include "allsessiondialog.h"
#include "ui_allsessiondialog.h"

AllSessionDialog::AllSessionDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllSessionDialog)
{
    ui->setupUi(this);
}

AllSessionDialog::~AllSessionDialog()
{
    delete ui;
}

void AllSessionDialog::on_act_create_triggered()
{

}

void AllSessionDialog::on_act_attribute_triggered()
{

}

void AllSessionDialog::on_btn_connect_clicked()
{

}

void AllSessionDialog::on_btn_close_clicked()
{
    this->close();
}
