#include "splitterm.h"

#include "konsolewidget.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>
#include <QTimer>

SplitTerm::SplitTerm(QWidget *parent) : QWidget(parent)
{
    //TODO: Transparency like in Konsole
    setAutoFillBackground(false);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    s = new QSplitter(this);
    layout->addWidget(s);
    KonsoleWidget* kk = new KonsoleWidget(this);
    k = kk;
    s->addWidget(kk);
    connect(kk, SIGNAL(closed()), this, SLOT(childClosed()));
    connect(kk, SIGNAL(splitEvent(Qt::Orientation)), this, SLOT(addSplitTerm(Qt::Orientation)));
}

SplitTerm::SplitTerm(QWidget *parent, QWidget *konsole)
{

    //TODO: Transparency like in Konsole
    setAutoFillBackground(false);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    s = new QSplitter(this);
    layout->addWidget(s);
    KonsoleWidget* kk = qobject_cast<KonsoleWidget*>(konsole);
    kk->setParent(this);
    k = kk;
    s->addWidget(kk);
    connect(kk, SIGNAL(closed()), this, SLOT(childClosed()));
    connect(kk, SIGNAL(splitEvent(Qt::Orientation)), this, SLOT(addSplitTerm(Qt::Orientation)));
}

SplitTerm::~SplitTerm()
{
}

void SplitTerm::addSplitTerm(Qt::Orientation dir)
{
    //Assume that split can be done only once.
    k->disconnect(this);
    s->setOrientation(dir);
    SplitTerm* t1 = new SplitTerm(this, k);
    SplitTerm* t2 = new SplitTerm(this);
    s->addWidget(t1);
    s->addWidget(t2);

    connect(t1, SIGNAL(closed()), this, SLOT(childClosed()));
    connect(t2, SIGNAL(closed()), this, SLOT(childClosed()));
}

void SplitTerm::childClosed()
{
    //TODO: Do better scrap.
    // Should:
    int cnt = 0;
    for (int i=0;i<s->count();++i) {
        QWidget* w = s->widget(i);
        if (!w->isHidden()) {
            cnt++;
        }
    }
    qDebug() << s->count() << cnt;
    if (!cnt) {
        close();
        emit closed();
    }
}
