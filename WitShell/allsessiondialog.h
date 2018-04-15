#ifndef ALLSESSIONDIALOG_H
#define ALLSESSIONDIALOG_H

#include <QMainWindow>

namespace Ui {
class AllSessionDialog;
}

class AllSessionDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit AllSessionDialog(QWidget *parent = 0);
    ~AllSessionDialog();


Q_SIGNALS:
    void connectSession(int index);

private slots:
    void on_act_create_triggered();

    void on_btn_connect_clicked();

    void on_btn_close_clicked();

    void on_act_attribute_triggered();

private:
    Ui::AllSessionDialog *ui;
};

#endif // ALLSESSIONDIALOG_H
