#include "konsolewidget.h"

#include <QResizeEvent>
#include <kconfig.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <kservice.h>
#include <kstandardaction.h>
#include <kstatusbar.h>
#include <kurl.h>
#include <QDebug>
#include <kparts/partmanager.h>

#include <QApplication>
#include <QBoxLayout>
#include <QMenu>
#include <kaction.h>
#include <kactioncollection.h>
#include <KXMLGUIFactory>

KonsoleWidget::KonsoleWidget(QWidget* parent) : QWidget(parent)
{
    m_split_act_h = new QAction("Split H", this);
    m_split_act_v = new QAction("Split V", this);
    connect(m_split_act_h, SIGNAL(triggered()), this, SLOT(splitActionH()));
    connect(m_split_act_v, SIGNAL(triggered()), this, SLOT(splitActionV()));
    //TODO: Transparency like in Konsole
    setAutoFillBackground(false);

    //query the .desktop file to load the requested Part
    KService::Ptr service = KService::serviceByDesktopName("konsolepart");

    if (service)
    {
      m_part = service->createInstance<KParts::ReadOnlyPart>(0);

      if (m_part)
      {
          QLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
          setLayout(layout);
          layout->setSpacing(0);
          layout->setContentsMargins(0, 0, 0, 0);
          layout->addWidget(m_part->widget());
          m_statusbar = new QLabel("TEST", this);
          layout->addWidget(m_statusbar);
          connect(m_part, SIGNAL(setWindowCaption(QString)), m_statusbar, SLOT(setText(QString)));
          m_term = qobject_cast<TerminalInterface*>(m_part->widget());
          connect(m_part, SIGNAL(destroyed(QObject*)), this, SLOT(terminalClosed()));
          static bool tc = true;
          if (tc) {
              tc = false;
              //m_part->setDOMDocument();
              qDebug() << m_part->domDocument().toString();
          }

      }
      else
      {
          KMessageBox::error(this, ki18n("Service konsolepart cannot be launched").toString());
          qApp->quit();
          return;
      }
    }
    else
    {
        KMessageBox::error(this, ki18n("Service konsolepart was not found").toString());
        qApp->quit();
        return;
    }

    setMinimumSize(QSize(100, 100));
}

KonsoleWidget::~KonsoleWidget()
{
}

void KonsoleWidget::terminalClosed()
{
    qDebug() << "TERM CLOSED";
    close();
    emit closed();
}

void KonsoleWidget::splitActionH() {
    splitAction(Qt::Horizontal);
}

void KonsoleWidget::splitActionV() {
    splitAction(Qt::Vertical);
}

void KonsoleWidget::splitAction(Qt::Orientation dir)
{
    emit splitEvent(dir);
}

void KonsoleWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu m_context_menu;
    m_context_menu.addAction(m_split_act_h);
    m_context_menu.addAction(m_split_act_v);
    m_context_menu.exec(event->globalPos());
    event->accept();
}
