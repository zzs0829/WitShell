#ifndef ALLSESSIONDIALOG_H
#define ALLSESSIONDIALOG_H

#include <QMainWindow>
#include "sessionattribute.h"
#include "settingsession.h"

namespace Ui {
class AllSessionDialog;
}

class AllSessionDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit AllSessionDialog(QWidget *parent = 0);
    ~AllSessionDialog();

    SessionAttribute *getSessions(int index);

Q_SIGNALS:
    void connectSession(int index);

protected:
    QString newSessionName() const;
    SessionAttribute *createSerialSession();
    void appendSession(SessionAttribute *session);
    void appendSessionTable(SessionAttribute *session);

private slots:
    void on_act_create_triggered();

    void on_btn_connect_clicked();

    void on_btn_close_clicked();

    void on_act_attribute_triggered();

    void on_tbl_sessions_itemSelectionChanged();

    void on_tbl_sessions_doubleClicked(const QModelIndex &index);

private:
    Ui::AllSessionDialog *ui;

    SettingSession *m_setting;
    QList<SessionAttribute *> m_sessions;

};

#endif // ALLSESSIONDIALOG_H
