#ifndef CONSOLETEXTEDIT_H
#define CONSOLETEXTEDIT_H

#include <QTextBrowser>
#include <QMouseEvent>

class ConsoleTextEdit : public QTextBrowser
{
    Q_OBJECT
public:
    explicit ConsoleTextEdit(QWidget *parent = 0);

    void putData(const QByteArray &data);

    void setLocalEchoEnabled(bool set);

signals:
    void getData(const QByteArray &data);

public slots:

protected:
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *e) Q_DECL_OVERRIDE;

private:
    bool localEchoEnabled;
    QString m_cmd;
    QStringList m_cmdHistorys;
    QFont m_font;
    QByteArray m_dataBuffer;
};

#endif // CONSOLETEXTEDIT_H
