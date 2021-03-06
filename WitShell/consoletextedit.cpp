#include "consoletextedit.h"
#include <QScrollBar>
#include <QDebug>

ConsoleTextEdit::ConsoleTextEdit(QWidget *parent) :
    QTextBrowser(parent)
  , localEchoEnabled(false)
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    setPalette(p);

}

void ConsoleTextEdit::putData(const QByteArray &data)
{
    m_dataBuffer.append(data);
    if(!m_dataBuffer.endsWith('\r')) { // 解决问题：接收到的换行"\r\n",如何分开接收会变成两个换行
        insertPlainText(QString(m_dataBuffer));

        QScrollBar *bar = verticalScrollBar();
        bar->setValue(bar->maximum());

        m_dataBuffer.clear();
    }
}

void ConsoleTextEdit::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void ConsoleTextEdit::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
        emit getData("\b");
        break;
    case Qt::Key_Left:
        emit getData("\x1B[D");
        break;
    case Qt::Key_Right:
        emit getData("\x1B[C");
        break;
    case Qt::Key_Up:
        emit getData("\x1B[A");
        qDebug() << e->text().toLocal8Bit();
        break;
    case Qt::Key_Down:
        emit getData("\x1B[B");
        break;
//    case Qt::Key_Tab:
//    case Qt::Key_Enter:
//    {
//        qDebug() << "Enter: " << m_cmd << e->text();
//        m_cmd.append(e->text());
//        emit getData(m_cmd.toLocal8Bit());
//        m_cmdHistorys.append(m_cmd);
//        m_cmd.clear();
//    }
//        break;
    default:
    {
//        if (localEchoEnabled)
//            QPlainTextEdit::keyPressEvent(e);
            emit getData(e->text().toLocal8Bit());
//        m_cmd.append(e->text());
//        qDebug() << "Enter 00 : "<< e->key() << m_cmd << e->text();
    }
    }
}

void ConsoleTextEdit::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void ConsoleTextEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void ConsoleTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
