#pragma once

#include <QWidget>
#include <kparts/part.h>
#include <QLabel>
#include <QMenu>
#include <QStatusBar>
#include <kde_terminal_interface.h>

class KonsoleWidget : public QWidget
{
    Q_OBJECT
public:
    KonsoleWidget(QWidget* parent = NULL);
    virtual ~KonsoleWidget();
public slots:
    void terminalClosed();
private slots:
    void splitActionH();
    void splitActionV();
    void splitAction(Qt::Orientation);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void closed();
    void splitEvent(Qt::Orientation);
private:
    QLabel *m_statusbar;
    KParts::ReadOnlyPart *m_part;
    TerminalInterface *m_term;
    QAction *m_split_act_h;
    QAction *m_split_act_v;
};
